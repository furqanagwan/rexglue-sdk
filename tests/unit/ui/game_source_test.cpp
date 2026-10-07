// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>
#include <windows.h>
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
    root = std::filesystem::temp_directory_path() /
           ("rex-source-ui-test-" + std::to_string(GetCurrentProcessId()));
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
    std::filesystem::remove(root / "source.iso", ec);
    const auto extracted = root / "extracted";
    // This child belongs to this newly created fixture; resolve before deletion.
    if (!std::filesystem::is_symlink(extracted, ec) &&
        std::filesystem::weakly_canonical(extracted, ec).parent_path() ==
            std::filesystem::weakly_canonical(root, ec))
      std::filesystem::remove_all(extracted, ec);
    std::filesystem::remove(root, ec);
    rex::cvar::testing::ResetAllForTesting();
  }
  void Show(rex::ui::LaunchPadSource pad = {}, rex::ui::GameSourceVisualsProvider visuals = {}) {
    dialog = new rex::ui::GameSourceDialog(
        drawer.get(), expected, root / "settings.toml",
        [this](std::filesystem::path source) {
          dialog = nullptr;
          ++completed;
          selected = std::move(source);
        },
        root, "", "default.xex", {}, std::move(pad), std::move(visuals));
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

TEST_CASE("Source and recovery dialogs use the private console message-box controls",
          "[ui][game_source][message_box][local]") {
  const char* path = std::getenv("REXGLUE_GUIDE_FLASH");
  if (!path || !*path)
    SKIP("REXGLUE_GUIDE_FLASH is not set");
  std::string error;
  auto modules = rex::ui::xui::SystemUpdate::ReadModules(std::filesystem::path(path), &error);
  REQUIRE(modules);
  std::shared_ptr<const rex::ui::guide::GuideAssets> assets =
      rex::ui::guide::GuideAssets::FromUpdate(
          rex::ui::xui::SystemUpdate::FromModules(*modules, &error), &error);
  REQUIRE(assets);
  rex::ui::GameSourceVisualsProvider visuals = [assets] {
    return std::optional(rex::ui::GameSourceVisuals{assets, {}, {}});
  };
  SourceHarness h;
  SECTION("Source choice uses the console's third-button visual") {
    h.Show({}, visuals);
    auto* window = ImGui::FindWindowByName("Choose game files");
    REQUIRE(window);
    const auto seed = window->GetID("Console choices");
    ImGui::ActivateItemByID(ImHashStr("Button1", 0, seed));
    h.Frame();
    CHECK_FALSE(GImGui->OpenPopupStack.empty());  // native Disc choice reached the drive picker
    CHECK(h.completed == 0);
  }
  SECTION("Extraction uses Active Downloads and publishes completed copy history") {
    std::vector<uint8_t> iso(128 * 2048);
    const std::string magic = "MICROSOFT*XBOX*MEDIA";
    auto put32 = [&](size_t at, uint32_t value) {
      for (int byte = 0; byte < 4; ++byte)
        iso[at + byte] = uint8_t(value >> (byte * 8));
    };
    std::memcpy(iso.data() + 32 * 2048, magic.data(), magic.size());
    std::memcpy(iso.data() + 33 * 2048 - magic.size(), magic.data(), magic.size());
    put32(32 * 2048 + 20, 34);
    put32(32 * 2048 + 24, 28);
    put32(34 * 2048 + 4, 35);
    put32(34 * 2048 + 8, 128);
    iso[34 * 2048 + 13] = 11;
    std::memcpy(iso.data() + 34 * 2048 + 14, "default.xex", 11);
    {
      std::ifstream xex(h.root / "default.xex", std::ios::binary);
      xex.read(reinterpret_cast<char*>(iso.data() + 35 * 2048), 128);
    }
    {
      std::ofstream file(h.root / "source.iso", std::ios::binary);
      file.write(reinterpret_cast<const char*>(iso.data()), iso.size());
    }
    std::vector<rex::ui::guide::GuideActivity> history;
    h.dialog = new rex::ui::GameSourceDialog(
        h.drawer.get(), h.expected, h.root / "settings.toml",
        [&](std::filesystem::path source) {
          h.dialog = nullptr;
          ++h.completed;
          h.selected = std::move(source);
        },
        h.root / "source.iso", "", "default.xex", h.root / "extracted", {}, visuals,
        [&](rex::ui::guide::GuideActivity item) { history.push_back(std::move(item)); });
    h.Frame();
    h.Frame();
    h.Press("Check source");
    for (int i = 0; i < 1000 && history.empty(); ++i) {
      h.Frame();
      h.Press("Extract to this PC");
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    REQUIRE(history.size() == 1);
    CHECK(history[0].status == "Completed");
    CHECK_FALSE(history[0].cancel);
    CHECK(h.completed == 0);
    const auto copied = h.root / "extracted" / ("game-" + h.expected.executable_checksum);
    CHECK(std::filesystem::is_regular_file(copied / "default.xex"));
    h.Press("Use this source");
    CHECK(h.completed == 1);
    CHECK(h.selected == copied);
  }
  SECTION("Controller A uses the recovery dialog's safe initial Leave choice") {
    rex::ui::LaunchPadState pad;
    bool completed = false, retried = true;
    rex::ui::GameMediaRecoveryDialog* dialog = nullptr;
    dialog = new rex::ui::GameMediaRecoveryDialog(
        h.drawer.get(), true, "",
        [&](bool retry) {
          completed = true;
          retried = retry;
          dialog = nullptr;
        },
        [&] { return std::optional(pad); }, visuals);
    for (int i = 0; i < 4; ++i)
      h.Frame(dialog);
    pad.activate = true;
    for (int i = 0; i < 4 && dialog; ++i)
      h.Frame(dialog);
    CHECK(completed);
    CHECK_FALSE(retried);
    CHECK(dialog == nullptr);
    delete dialog;
  }
  SECTION("Recovery chooses Retry through the console visual") {
    bool retried = false;
    rex::ui::GameMediaRecoveryDialog* dialog = nullptr;
    dialog = new rex::ui::GameMediaRecoveryDialog(
        h.drawer.get(), true, "",
        [&](bool retry) {
          retried = retry;
          dialog = nullptr;
        },
        {}, visuals);
    h.Frame(dialog);
    h.Frame(dialog);
    auto* window = ImGui::FindWindowByName("Game source unavailable");
    REQUIRE(window);
    const auto seed = window->GetID("Console choices");
    CHECK(GImGui->NavId == ImHashStr("Button1", 0, seed));  // safe initial Leave choice
    ImGui::ActivateItemByID(ImHashStr("Button0", 0, seed));
    h.Frame(dialog);
    CHECK(retried);
    CHECK(dialog == nullptr);
    delete dialog;
  }
}
