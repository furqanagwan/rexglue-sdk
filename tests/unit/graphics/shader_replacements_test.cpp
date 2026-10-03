/**
 * @file        shader_replacements_test.cpp
 * @brief       Replacement shaders matched by ucode hash, with fallback (RG-GDK-067)
 */

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/pipeline/shader/replacements.h>

namespace {

using rex::graphics::ShaderReplacements;
using Stage = ShaderReplacements::Stage;

std::vector<uint8_t> Dxbc(uint8_t tag) {
  std::vector<uint8_t> dxbc(32, tag);
  dxbc[0] = 'D', dxbc[1] = 'X', dxbc[2] = 'B', dxbc[3] = 'C';
  return dxbc;
}

}  // namespace

TEST_CASE("Replacement names give the hash, stage and modification", "[graphics][replacements]") {
  ShaderReplacements::Key key;
  REQUIRE(ShaderReplacements::ParseName("00112233AABBCCDD.vs.dxbc", key));
  CHECK(key.ucode_hash == 0x00112233AABBCCDDull);
  CHECK(key.stage == Stage::kVertex);
  CHECK_FALSE(key.modification.has_value());

  REQUIRE(ShaderReplacements::ParseName("00112233aabbccdd_0000000000000042.ps_rov.dxbc", key));
  CHECK(key.stage == Stage::kPixelRov);
  CHECK(key.modification == 0x42u);

  // Wrong length, unknown stage, wrong extension, no stage.
  CHECK_FALSE(ShaderReplacements::ParseName("112233.vs.dxbc", key));
  CHECK_FALSE(ShaderReplacements::ParseName("00112233AABBCCDD.gs.dxbc", key));
  CHECK_FALSE(ShaderReplacements::ParseName("00112233AABBCCDD.vs.hlsl", key));
  CHECK_FALSE(ShaderReplacements::ParseName("00112233AABBCCDD.dxbc", key));
  CHECK_FALSE(ShaderReplacements::ParseName("00112233AABBCCDD_12.vs.dxbc", key));
}

TEST_CASE("An exact modification wins, any modification is next, else translate",
          "[graphics][replacements]") {
  ShaderReplacements replacements;
  constexpr uint64_t kHash = 0x1234567890ABCDEFull;
  REQUIRE(replacements.Add({kHash, Stage::kPixelRtv, std::nullopt}, Dxbc(1)));
  REQUIRE(replacements.Add({kHash, Stage::kPixelRtv, 7}, Dxbc(2)));

  const std::vector<uint8_t>* found = replacements.Find(kHash, Stage::kPixelRtv, 7);
  REQUIRE(found);
  CHECK((*found)[4] == 2);
  found = replacements.Find(kHash, Stage::kPixelRtv, 8);
  REQUIRE(found);
  CHECK((*found)[4] == 1);

  // Another stage, path or hash: no replacement, so the translation stays.
  CHECK(replacements.Find(kHash, Stage::kPixelRov, 7) == nullptr);
  CHECK(replacements.Find(kHash, Stage::kVertex, 7) == nullptr);
  CHECK(replacements.Find(kHash + 1, Stage::kPixelRtv, 7) == nullptr);

  // Only DXBC containers are taken.
  CHECK_FALSE(replacements.Add({kHash, Stage::kVertex, std::nullopt}, std::vector<uint8_t>(32, 0)));
  CHECK(replacements.size() == 2);
}

TEST_CASE("A replacement folder loads the named DXBC files only", "[graphics][replacements]") {
  const std::filesystem::path folder =
      std::filesystem::temp_directory_path() / "rexglue_shader_replacements_test";
  std::filesystem::remove_all(folder);
  std::filesystem::create_directories(folder);
  auto write = [&](const char* name, const std::vector<uint8_t>& data) {
    std::ofstream(folder / name, std::ios::binary)
        .write(reinterpret_cast<const char*>(data.data()), std::streamsize(data.size()));
  };
  write("00000000000000A1.vs.dxbc", Dxbc(3));
  write("00000000000000A2.ps_rtv.dxbc", std::vector<uint8_t>(32, 0));  // not DXBC
  write("readme.dxbc", Dxbc(4));                                       // bad name
  write("00000000000000A3.ps_rtv.hlsl", Dxbc(5));                      // source, not shipped

  ShaderReplacements replacements;
  CHECK(replacements.Load(folder) == 1);
  CHECK(replacements.Find(0xA1, Stage::kVertex, 0) != nullptr);
  CHECK(replacements.Find(0xA2, Stage::kPixelRtv, 0) == nullptr);
  CHECK(ShaderReplacements().Load(folder / "missing") == 0);
  std::filesystem::remove_all(folder);
}
