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

/// An image in premultiplied BGRA, 8 bits a channel, rows top down.
struct Image {
  int width = 0;
  int height = 0;
  std::vector<uint8_t> pixels;

  uint8_t* at(int x, int y) { return &pixels[(size_t(y) * width + x) * 4]; }
  const uint8_t* at(int x, int y) const { return &pixels[(size_t(y) * width + x) * 4]; }
};

/// Decodes a PNG, JPEG or any format Windows Imaging Component reads.
std::optional<Image> DecodeImage(std::span<const uint8_t> bytes, std::string* error);
/// Encodes `image` as a PNG (straight alpha, as PNG stores it).
std::optional<std::vector<uint8_t>> EncodePng(const Image& image, std::string* error);
/// A Windows ICO at 16, 24, 32, 48, 64, 128 and 256 pixels (PNG at 256,
/// bitmap frames below 256 for native Shell extraction).
/// Uses title art directly, preserving alpha, independently of library tiles.
std::optional<std::vector<uint8_t>> EncodeIco(const Image& image, std::string* error);
/// `image` scaled to `width` x `height` with high-quality cubic filtering.
Image Resize(const Image& image, int width, int height);

/// The orb and XBOX 360 wordmark the tile's strip shows, shaped from the
/// system update's `splash_360.png` (xam shared resources) without its trade
/// mark signs, and coloured as the Store's tiles colour them: the white orb
/// with a green X, XBOX dark green, 360 grey.
struct StripArt {
  Image orb;       // turned a quarter left as the strip shows it; transparent outside the disc
  Image wordmark;  // left to right
};
std::optional<StripArt> StripArtFromSplash(const Image& splash, std::string* error);

/// The square tile the Xbox PC app shows for an Xbox 360 backward-compatible
/// game, `size` pixels across (laid out from the Store's 1080 x 1080 tiles):
/// a white strip down the left 17.5% with the green swooshes at its top, the
/// wordmark reading upwards and the orb at its foot, and `cover` filling the
/// rest, scaled to cover it and centred. `crop_top` (0 to 1) is cut from the
/// top of `cover` first: the 360 marketplace's box art carries the console's
/// banner there. Without `strip_art` the strip has the swooshes only.
Image ComposeTile(const Image& cover, double crop_top, const StripArt* strip_art, int size);

/// `image` scaled to cover `width` x `height` and centred, for the splash.
Image Cover(const Image& image, int width, int height);

}  // namespace rexglue::cli
