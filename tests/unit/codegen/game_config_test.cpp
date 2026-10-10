/**
 * @file        game_config_test.cpp
 * @brief       MicrosoftGame.config generation from supplied identity (RG-GDK-022)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include <rex/codegen/game_config.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb_image.h>

using rex::codegen::GameConfigIdentity;
using rex::codegen::RenderGameConfig;
using rex::codegen::ValidateGameConfigIdentity;

namespace {

GameConfigIdentity Minimal() {
  GameConfigIdentity id;
  id.name = "Example.RecompiledTitle";
  id.publisher = "CN=Example Studio";
  id.display_name = "Recompiled Title";
  id.publisher_display_name = "Example Studio";
  id.executable = "recompiled_title.exe";
  return id;
}

bool Contains(const std::string& text, const std::string& part) {
  return text.find(part) != std::string::npos;
}

}

TEST_CASE("A config from minimal identity names no service IDs", "[gameconfig]") {
  auto xml = RenderGameConfig(Minimal());
  REQUIRE(xml);
  CHECK(Contains(*xml, "<Game configVersion=\"1\">"));
  CHECK(Contains(*xml,
                 "<Identity Name=\"Example.RecompiledTitle\" Publisher=\"CN=Example Studio\" "
                 "Version=\"1.0.0.0\"/>"));
  CHECK(Contains(*xml,
                 "<Executable Name=\"recompiled_title.exe\" TargetDeviceFamily=\"PC\" "
                 "Architecture=\"x64\" Id=\"Game\"/>"));
  CHECK(Contains(*xml, "DefaultDisplayName=\"Recompiled Title\""));
  CHECK(Contains(*xml, "Square150x150Logo=\"Square150x150Logo.png\""));
  CHECK(Contains(*xml, "SplashScreenImage=\"SplashScreen.png\""));
  CHECK(Contains(*xml, "<KnownDependency Name=\"VC14\"/>"));
  for (const char* id : {"<TitleId>", "<MSAAppId>", "<StoreId>", "RequiresXboxLive"}) {
    INFO(id);
    CHECK_FALSE(Contains(*xml, id));
  }
}

TEST_CASE("Supplied Partner Center IDs are written as given", "[gameconfig]") {
  auto id = Minimal();
  id.title_id = "1A2B3C4D";
  id.msa_app_id = "000000004C27D3A1";
  id.store_id = "9NBLGGH4R315";
  auto xml = RenderGameConfig(id);
  REQUIRE(xml);
  CHECK(Contains(*xml, "<TitleId>1A2B3C4D</TitleId>"));
  CHECK(Contains(*xml, "<MSAAppId>000000004C27D3A1</MSAAppId>"));
  CHECK(Contains(*xml, "<StoreId>9NBLGGH4R315</StoreId>"));
}

TEST_CASE("Display text is XML-escaped", "[gameconfig]") {
  auto id = Minimal();
  id.display_name = "Tom & Jerry's <Remix> \"HD\"";
  id.description = "A & B";
  auto xml = RenderGameConfig(id);
  REQUIRE(xml);
  CHECK(
      Contains(*xml, "DefaultDisplayName=\"Tom &amp; Jerry&apos;s &lt;Remix&gt; &quot;HD&quot;\""));
  CHECK(Contains(*xml, "Description=\"A &amp; B\""));
}

TEST_CASE("Identity that the GDK schema rejects is refused", "[gameconfig]") {
  auto check = [](auto mutate, const char* field) {
    auto id = Minimal();
    mutate(id);
    auto result = ValidateGameConfigIdentity(id);
    INFO(field);
    REQUIRE_FALSE(result);
    CHECK(Contains(result.error().message, field));
    CHECK_FALSE(RenderGameConfig(id));
  };
  check([](auto& id) { id.name = "My_Game"; }, "Identity name");
  check([](auto& id) { id.name = "ab"; }, "Identity name");
  check([](auto& id) { id.name = std::string(51, 'a'); }, "Identity name");
  check([](auto& id) { id.publisher = "Example Studio"; }, "Publisher");
  check([](auto& id) { id.publisher = "CN=A,B"; }, "Publisher");
  check([](auto& id) { id.version = "1.0.0"; }, "Version");
  check([](auto& id) { id.version = "1.0.0.65536"; }, "Version");
  check([](auto& id) { id.version = "01.0.0.0"; }, "Version");
  check([](auto& id) { id.display_name = " padded"; }, "Display name");
  check([](auto& id) { id.display_name = std::string(257, 'x'); }, "Display name");
  check([](auto& id) { id.publisher_display_name = ""; }, "Publisher display name");
  check([](auto& id) { id.description = "line\nbreak"; }, "Description");
  check([](auto& id) { id.background_color = "black"; }, "Background color");
  check([](auto& id) { id.executable = "game.dll"; }, "Executable");
  check([](auto& id) { id.executable = "C:\\games\\game.exe"; }, "Executable");
  check([](auto& id) { id.executable = "..\\game.exe"; }, "Executable");
  check([](auto& id) { id.executable = "\\game.exe"; }, "Executable");
  check([](auto& id) { id.title_id = "00000000", id.msa_app_id = "123"; }, "Title ID");
  check(
      [](auto& id) {
        id.title_id = "1A2B3C4";
        id.msa_app_id = "123";
      },
      "Title ID");
  check(
      [](auto& id) {
        id.title_id = "1A2B3C4D";
        id.msa_app_id = "0000";
      },
      "MSA app ID");
  check([](auto& id) { id.title_id = "1A2B3C4D"; }, "Title ID and MSA app ID");
  check([](auto& id) { id.msa_app_id = "123"; }, "Title ID and MSA app ID");
  check([](auto& id) { id.store_id = "9NBLGGH4R31A"; }, "Store ID");
}

TEST_CASE("Accepted identity variants", "[gameconfig]") {
  auto id = Minimal();
  id.executable = "bin\\x64/Game.EXE";
  id.publisher = "CN=Example, O=Studio, C=GB";
  id.version = "65535.0.10.9";
  id.name = "a-b.c";
  CHECK(ValidateGameConfigIdentity(id));
}

TEST_CASE("Placeholder images are flat RGBA at the size the config names", "[gameconfig]") {
  for (const auto& image : rex::codegen::GameConfigImages()) {
    INFO(image.file_name);
    const auto png = rex::codegen::SolidColorPng(image.width, image.height, 0x1E90FF);
    int width = 0, height = 0, channels = 0;
    stbi_uc* pixels =
        stbi_load_from_memory(png.data(), int(png.size()), &width, &height, &channels, 4);
    REQUIRE(pixels);
    CHECK(width == int(image.width));
    CHECK(height == int(image.height));

    CHECK(channels == 4);
    bool uniform = true;
    for (size_t i = 0; i < size_t(width) * height; ++i) {
      const stbi_uc* p = pixels + i * 4;
      uniform &= p[0] == 0x1E && p[1] == 0x90 && p[2] == 0xFF && p[3] == 0xFF;
    }
    CHECK(uniform);
    stbi_image_free(pixels);

    CHECK(png.size() < size_t(image.width) * image.height * 4 / 10 + 100);
  }
}
