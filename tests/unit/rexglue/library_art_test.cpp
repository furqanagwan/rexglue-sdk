/**
 * @file        tests/unit/rexglue/library_art_test.cpp
 * @brief       Xbox 360 backward-compatibility style library tiles (RG-GDK-068)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <cstdint>
#include <array>

#include "rexglue/commands/library_art.h"

using rexglue::cli::ComposeTile;
using rexglue::cli::DecodeImage;
using rexglue::cli::EncodePng;
using rexglue::cli::Image;
using rexglue::cli::StripArt;
using rexglue::cli::StripArtFromSplash;

TEST_CASE("Native title ICO frames retain size colour and transparency", "[library_art][icon]") {
  Image source{256, 256, std::vector<uint8_t>(256 * 256 * 4)};
  for (size_t i = 0; i < source.pixels.size(); i += 4) {
    source.pixels[i] = 32;
    source.pixels[i + 1] = 64;
    source.pixels[i + 2] = 96;
    source.pixels[i + 3] = 128;
  }
  std::string error;
  const auto ico = rexglue::cli::EncodeIco(source, &error);
  REQUIRE(ico);
  REQUIRE(ico->size() > 118);
  auto read32 = [&ico](size_t offset) {
    uint32_t value = 0;
    for (int i = 0; i < 4; ++i)
      value |= uint32_t((*ico)[offset + i]) << (8 * i);
    return value;
  };
  CHECK((*ico)[0] == 0);
  CHECK((*ico)[2] == 1);
  CHECK((*ico)[4] == 7);
  constexpr std::array<int, 7> sizes = {16, 24, 32, 48, 64, 128, 256};
  size_t end = 118;
  for (size_t i = 0; i < sizes.size(); ++i) {
    const size_t entry = 6 + i * 16;
    const auto length = read32(entry + 8);
    const auto offset = read32(entry + 12);
    REQUIRE(offset == end);
    REQUIRE(size_t(offset) + length <= ico->size());
    CHECK((*ico)[entry] == uint8_t(sizes[i]));
    if (sizes[i] == 256) {
      const auto decoded =
          DecodeImage(std::span<const uint8_t>(*ico).subspan(offset, length), &error);
      REQUIRE(decoded);
      CHECK(decoded->width == sizes[i]);
      CHECK(decoded->height == sizes[i]);
      CHECK(decoded->at(sizes[i] / 2, sizes[i] / 2)[0] == 32);
      CHECK(decoded->at(sizes[i] / 2, sizes[i] / 2)[3] == 128);
    } else {
      CHECK(read32(offset) == 40);
      CHECK(read32(offset + 4) == uint32_t(sizes[i]));
      CHECK(read32(offset + 8) == uint32_t(sizes[i] * 2));
      CHECK((*ico)[offset + 40] == 64);  // Straight blue, not premultiplied.
      CHECK((*ico)[offset + 43] == 128);
    }
    end = size_t(offset) + length;
  }
  CHECK(end == ico->size());
  CHECK_FALSE(rexglue::cli::EncodeIco(Image{}, &error));
  source.pixels.pop_back();
  CHECK_FALSE(rexglue::cli::EncodeIco(source, &error));
}

namespace {

Image Solid(int width, int height, uint8_t r, uint8_t g, uint8_t b) {
  Image image;
  image.width = width;
  image.height = height;
  for (int i = 0; i < width * height; ++i) {
    image.pixels.insert(image.pixels.end(), {b, g, r, 255});
  }
  return image;
}

void Fill(Image& image, int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b) {
  for (int y = y0; y < y1; ++y) {
    for (int x = x0; x < x1; ++x) {
      uint8_t* p = image.at(x, y);
      p[0] = b, p[1] = g, p[2] = r, p[3] = 255;
    }
  }
}

struct Rgb {
  int r, g, b;
};
Rgb At(const Image& image, int x, int y) {
  const uint8_t* p = image.at(x, y);
  return {p[2], p[1], p[0]};
}

}  // namespace

TEST_CASE("Library art PNGs round-trip", "[library_art]") {
  Image image = Solid(3, 2, 10, 20, 30);
  Fill(image, 2, 1, 3, 2, 200, 100, 50);
  std::string error;
  const auto png = EncodePng(image, &error);
  REQUIRE(png);
  const auto read = DecodeImage(*png, &error);
  REQUIRE(read);
  CHECK(read->width == 3);
  CHECK(read->height == 2);
  CHECK(read->pixels == image.pixels);
  CHECK_FALSE(DecodeImage(std::vector<uint8_t>{1, 2, 3}, &error));
}

TEST_CASE("The tile is the strip beside the box art without its banner", "[library_art]") {
  // Marketplace-style box art: a blue banner over the top 13%, red below.
  Image cover = Solid(219, 300, 220, 0, 0);
  Fill(cover, 0, 0, 219, 39, 0, 0, 220);
  const Image tile = ComposeTile(cover, 0.13, nullptr, 1080);
  REQUIRE(tile.width == 1080);
  REQUIRE(tile.height == 1080);
  // The art fills everything right of the strip, banner gone.
  for (int y : {2, 540, 1077}) {
    for (int x : {192, 600, 1077}) {
      INFO(x << ", " << y);
      CHECK(At(tile, x, y).r > 200);
      CHECK(At(tile, x, y).b < 20);
    }
  }
  // The strip: green swooshes at the top, white below.
  const Rgb top = At(tile, 20, 60);
  CHECK(top.g > top.r);
  CHECK(top.g > top.b + 100);
  for (int y : {600, 900}) {
    const Rgb white = At(tile, 95, y);
    CHECK(white.r == 255);
    CHECK(white.g == 255);
    CHECK(white.b == 255);
  }
  // Scaled down for the smaller sizes, the layout holds.
  const Image small = ComposeTile(cover, 0.13, nullptr, 150);
  CHECK(small.width == 150);
  CHECK(At(small, 13, 75).r > 240);   // strip
  CHECK(At(small, 100, 75).r > 200);  // art
}

TEST_CASE("The strip's orb and wordmark come from the console's splash", "[library_art]") {
  // A splash in splash_360.png's layout: the orb, a gap, the wordmark (a
  // green word and a grey one) with a trade mark sign at its baseline.
  Image splash = Solid(300, 200, 0, 0, 0);
  for (uint8_t& v : splash.pixels) {
    v = 0;
  }
  for (int y = 10; y < 90; ++y) {
    for (int x = 110; x < 190; ++x) {
      if (std::hypot(x + 0.5 - 150, y + 0.5 - 50) < 40) {
        Fill(splash, x, y, x + 1, y + 1, 200, 200, 200);
      }
    }
  }
  Fill(splash, 140, 30, 160, 70, 40, 180, 20);      // the X
  Fill(splash, 10, 120, 120, 170, 100, 190, 30);    // XBOX
  Fill(splash, 130, 120, 250, 170, 120, 120, 120);  // 360
  Fill(splash, 253, 163, 263, 170, 120, 120, 120);  // trade mark sign
  std::string error;
  const auto art = StripArtFromSplash(splash, &error);
  REQUIRE(art);
  CHECK(art->orb.width == 80);
  CHECK(art->orb.height == 80);
  CHECK(art->orb.at(40, 40)[3] == 255);  // inside the disc
  CHECK(art->orb.at(1, 1)[3] == 0);      // outside it
  const Rgb x = At(art->orb, 40, 40);    // the X, in the tiles' green
  CHECK(x.g > x.r + 60);
  // The wordmark without the trade mark sign, recoloured.
  CHECK(art->wordmark.width == 240);
  CHECK(art->wordmark.height == 50);
  const Rgb xbox = At(art->wordmark, 50, 25);
  CHECK(xbox.r == 16);
  CHECK(xbox.g == 120);
  const Rgb grey = At(art->wordmark, 180, 25);
  CHECK(grey.r == 104);
  CHECK(grey.g == 104);

  // Placed: the wordmark runs up the strip, the orb below it.
  const Image tile = ComposeTile(Solid(10, 10, 220, 0, 0), 0.0, &*art, 1080);
  const Rgb word = At(tile, 95, 850);  // the bottom of XBOX
  CHECK(word.g > word.r + 60);
  const Rgb orb = At(tile, 95, 986);
  CHECK(orb.r < 250);

  Image blank = Solid(50, 50, 0, 0, 0);
  for (uint8_t& v : blank.pixels) {
    v = 0;
  }
  CHECK_FALSE(StripArtFromSplash(blank, &error));
}
