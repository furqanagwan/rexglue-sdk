/**
 * @file        rex/codegen/game_config.h
 * @brief       PC MicrosoftGame.config generation for recompiled titles (RG-GDK-022)
 *
 * The config is built only from identity the title project supplies. Store
 * and Xbox services IDs (TitleId, MSAAppId, StoreId) are written only when
 * given, never invented; values are checked against the rules of the GDK's
 * GameConfigSchema.xsd (edition 260404) before anything is written.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include <rex/result.h>

namespace rex::codegen {

struct GameConfigIdentity {
  // Identity: Name (3-50 of A-Z a-z 0-9 . -) and Publisher (an X.500 name,
  // e.g. "CN=Example"). For a Store build both must equal Partner Center's.
  std::string name;
  std::string publisher;
  std::string version = "1.0.0.0";
  // ShellVisuals.
  std::string display_name;
  std::string publisher_display_name;
  std::string description;
  std::string background_color = "#000000";
  // The title executable, relative to the package root.
  std::string executable;
  // Xbox services identity, both or neither (from Partner Center).
  std::optional<std::string> title_id;
  std::optional<std::string> msa_app_id;
  // Microsoft Store product ID (12 characters).
  std::optional<std::string> store_id;
};

// A ShellVisuals image the config names, with the size GDK tools expect.
struct GameConfigImage {
  const char* attribute;
  const char* file_name;
  uint32_t width;
  uint32_t height;
};

std::span<const GameConfigImage> GameConfigImages();

// Checks every field; the error names the first bad one.
Result<void> ValidateGameConfigIdentity(const GameConfigIdentity& identity);

// The MicrosoftGame.config text (UTF-8 XML), or the validation error.
Result<std::string> RenderGameConfig(const GameConfigIdentity& identity);

// A single-color PNG, used for placeholder ShellVisuals images until the
// title supplies its own art.
std::vector<uint8_t> SolidColorPng(uint32_t width, uint32_t height, uint32_t rgb);

}  // namespace rex::codegen
