#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/pipeline/texture/util.h>

namespace texture_util = rex::graphics::texture_util;

TEST_CASE("2D tiled offsets match Xenos reference vectors", "[native_render][texture]") {
  CHECK(texture_util::GetTiledOffset2D(0, 0, 32, 2) == 0);
  CHECK(texture_util::GetTiledOffset2D(1, 0, 32, 2) == 4);
  CHECK(texture_util::GetTiledOffset2D(8, 0, 32, 2) == 64);
  CHECK(texture_util::GetTiledOffset2D(31, 31, 32, 2) == 3964);
  CHECK(texture_util::GetTiledOffset2D(32, 0, 64, 2) == 4096);
  CHECK(texture_util::GetTiledOffset2D(4, 7, 64, 3) == 1808);
}

TEST_CASE("3D tiled offsets match Xenos reference vectors", "[native_render][texture]") {
  CHECK(texture_util::GetTiledOffset3D(0, 0, 0, 32, 32, 2) == 0);
  CHECK(texture_util::GetTiledOffset3D(1, 0, 0, 32, 32, 2) == 4);
  CHECK(texture_util::GetTiledOffset3D(31, 31, 3, 32, 32, 2) == 16252);
  CHECK(texture_util::GetTiledOffset3D(32, 0, 0, 64, 32, 2) == 8192);
  CHECK(texture_util::GetTiledOffset3D(4, 7, 2, 64, 64, 3) == 10000);
}

TEST_CASE("Tiled address bounds cover complete edge tiles", "[native_render][texture]") {
  CHECK(texture_util::GetTiledAddressUpperBound2D(0, 1, 32, 2) == 0);
  CHECK(texture_util::GetTiledAddressUpperBound2D(1, 1, 32, 0) == 0xA00);
  CHECK(texture_util::GetTiledAddressUpperBound2D(32, 32, 32, 2) == 0x1000);
  CHECK(texture_util::GetTiledAddressUpperBound2D(33, 1, 64, 2) == 0x2000);

  CHECK(texture_util::GetTiledAddressUpperBound3D(1, 1, 0, 32, 32, 2) == 0);
  CHECK(texture_util::GetTiledAddressUpperBound3D(1, 1, 1, 32, 32, 2) == 0x4000);
  CHECK(texture_util::GetTiledAddressUpperBound3D(33, 1, 1, 64, 32, 2) == 0x8000);
}
