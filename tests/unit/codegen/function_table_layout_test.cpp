/**
 * @file        tests/unit/codegen/function_table_layout_test.cpp
 * @brief       Where each module's function dispatch table goes (RG-GDK-070)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/codegen/function_table_layout.h>

using rex::codegen::ModuleImage;
using rex::codegen::PlaceFunctionTables;

namespace {
constexpr uint32_t kThunks = 0x10000;
}

TEST_CASE("A lone module keeps its table after its image", "[codegen][function_table]") {
  const auto tables = PlaceFunctionTables({{0x82000000, 0x00A00000}}, kThunks);
  REQUIRE(tables.size() == 1);
  CHECK(tables[0] == 0x82A00000);
}

TEST_CASE("Tables move clear of a guest DLL's image", "[codegen][function_table]") {
  // FIFA Street: the launcher (1.75 MiB at 82000000) and its game DLL at
  // 82300000; the launcher's table after its image would cross the DLL.
  const ModuleImage launcher{0x82000000, 0x001C0000};
  const ModuleImage game{0x82300000, 0x01B00000};
  const auto tables = PlaceFunctionTables({launcher, game}, kThunks);
  REQUIRE(tables.size() == 2);
  const uint64_t launcher_table_end = uint64_t(tables[0]) + (launcher.size + kThunks) * 2;
  const uint64_t game_table_end = uint64_t(tables[1]) + (game.size + kThunks) * 2;
  // The DLL's own table still follows its image.
  CHECK(tables[1] == game.base + game.size);
  // The launcher's goes past every image, on a 64 KiB boundary, and the two
  // tables do not overlap.
  CHECK(tables[0] >= game.base + game.size);
  CHECK(tables[0] % 0x10000 == 0);
  CHECK((launcher_table_end <= tables[1] || game_table_end <= tables[0]));
  // Nothing lands on an image.
  for (const ModuleImage& image : {launcher, game}) {
    for (size_t i = 0; i < tables.size(); ++i) {
      const uint64_t size = (uint64_t((i ? game : launcher).size) + kThunks) * 2;
      CHECK((uint64_t(tables[i]) + size <= image.base || tables[i] >= image.base + image.size));
    }
  }
}
