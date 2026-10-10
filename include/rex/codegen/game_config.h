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
  std::string name;
  std::string publisher;
  std::string version = "1.0.0.0";

  std::string display_name;
  std::string publisher_display_name;
  std::string description;
  std::string background_color = "#000000";

  std::string executable;

  std::optional<std::string> title_id;
  std::optional<std::string> msa_app_id;

  std::optional<std::string> store_id;
};

struct GameConfigImage {
  const char* attribute;
  const char* file_name;
  uint32_t width;
  uint32_t height;
};

std::span<const GameConfigImage> GameConfigImages();

Result<void> ValidateGameConfigIdentity(const GameConfigIdentity& identity);

Result<std::string> RenderGameConfig(const GameConfigIdentity& identity);

std::vector<uint8_t> SolidColorPng(uint32_t width, uint32_t height, uint32_t rgb);

}
