/**
 * @file        rexglue/commands/library_art.h
 * @brief       Xbox 360 backward-compatibility style library tiles (RG-GDK-068)
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

namespace rexglue::cli {

struct Image {
  int width = 0;
  int height = 0;
  std::vector<uint8_t> pixels;

  uint8_t* at(int x, int y) { return &pixels[(size_t(y) * width + x) * 4]; }
  const uint8_t* at(int x, int y) const { return &pixels[(size_t(y) * width + x) * 4]; }
};

std::optional<Image> DecodeImage(std::span<const uint8_t> bytes, std::string* error);

std::optional<std::vector<uint8_t>> EncodePng(const Image& image, std::string* error);

std::optional<std::vector<uint8_t>> EncodeIco(const Image& image, std::string* error);

Image Resize(const Image& image, int width, int height);

struct StripArt {
  Image orb;
  Image wordmark;
};
std::optional<StripArt> StripArtFromSplash(const Image& splash, std::string* error);

Image ComposeTile(const Image& cover, double crop_top, const StripArt* strip_art, int size);

Image Cover(const Image& image, int width, int height);

}
