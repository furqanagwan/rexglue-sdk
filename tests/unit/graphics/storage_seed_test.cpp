/**
 * @file        tests/unit/graphics/storage_seed_test.cpp
 * @brief       A shader cache shipped with a title, seeding the player's (RG-GDK-064)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <rex/graphics/pipeline/shader/storage_seed.h>
#include <rex/hash.h>

using rex::graphics::SeedResult;
using rex::graphics::SeedStorageFile;
using rex::graphics::StorageFormat;

namespace {

using Bytes = std::vector<uint8_t>;

const uint8_t kHeader[] = {'X', 'E', 'S', 'H', 0x20, 0x20, 0x12, 0x19};
const uint8_t kOldHeader[] = {'X', 'E', 'S', 'H', 0x20, 0x19, 0x01, 0x01};
const StorageFormat kShaders{kHeader, 0};

Bytes Shader(uint32_t seed, uint32_t dwords) {
  std::vector<uint32_t> ucode(dwords);
  for (uint32_t i = 0; i < dwords; ++i) {
    ucode[i] = seed * 1000 + i;
  }
  const uint64_t hash = XXH3_64bits(ucode.data(), ucode.size() * 4);
  Bytes out(12 + dwords * 4);
  std::memcpy(&out[0], &hash, 8);
  const uint32_t field = dwords | (seed & 1u) << 31;
  std::memcpy(&out[8], &field, 4);
  std::memcpy(&out[12], ucode.data(), ucode.size() * 4);
  return out;
}

Bytes Pipeline(uint8_t seed) {
  Bytes body(24, seed);
  const uint64_t hash = XXH3_64bits(body.data(), body.size());
  Bytes out(8);
  std::memcpy(out.data(), &hash, 8);
  out.insert(out.end(), body.begin(), body.end());
  return out;
}

Bytes File(std::span<const uint8_t> header, std::initializer_list<Bytes> records) {
  Bytes out(header.begin(), header.end());
  for (const Bytes& r : records) {
    out.insert(out.end(), r.begin(), r.end());
  }
  return out;
}

struct TempDir {
  std::filesystem::path path;
  TempDir() {
    path = std::filesystem::temp_directory_path() /
           ("rexglue_seed_" + std::to_string(reinterpret_cast<uintptr_t>(this)));
    std::filesystem::remove_all(path);
    std::filesystem::create_directories(path);
  }
  ~TempDir() { std::filesystem::remove_all(path); }
  void Put(const char* name, const Bytes& bytes) const {
    std::ofstream(path / name, std::ios::binary)
        .write(reinterpret_cast<const char*>(bytes.data()), std::streamsize(bytes.size()));
  }
  Bytes Get(const char* name) const {
    std::ifstream file(path / name, std::ios::binary);
    return Bytes(std::istreambuf_iterator<char>(file), {});
  }
};

}

TEST_CASE("A shipped shader cache seeds a player without one", "[graphics][shader_cache]") {
  TempDir dir;
  const Bytes shipped = File(kHeader, {Shader(1, 3), Shader(2, 5)});
  dir.Put("shipped.xsh", shipped);
  auto outcome = SeedStorageFile(dir.path / "shipped.xsh", dir.path / "user.xsh", kShaders);
  CHECK(outcome.result == SeedResult::kCopied);
  CHECK(outcome.added == 2);
  CHECK(dir.Get("user.xsh") == shipped);

  outcome = SeedStorageFile(dir.path / "shipped.xsh", dir.path / "user.xsh", kShaders);
  CHECK(outcome.result == SeedResult::kUpToDate);
  CHECK(dir.Get("user.xsh") == shipped);

  CHECK(SeedStorageFile(dir.path / "none.xsh", dir.path / "user.xsh", kShaders).result ==
        SeedResult::kNoShippedFile);
}

TEST_CASE("Shipped records the player lacks are appended after theirs",
          "[graphics][shader_cache]") {
  TempDir dir;
  dir.Put("shipped.xsh", File(kHeader, {Shader(1, 3), Shader(2, 5), Shader(3, 1)}));

  Bytes user = File(kHeader, {Shader(2, 5), Shader(9, 4)});
  const Bytes cut = Shader(4, 8);
  user.insert(user.end(), cut.begin(), cut.begin() + 20);
  dir.Put("user.xsh", user);
  const auto outcome = SeedStorageFile(dir.path / "shipped.xsh", dir.path / "user.xsh", kShaders);
  CHECK(outcome.result == SeedResult::kMerged);
  CHECK(outcome.added == 2);
  CHECK(dir.Get("user.xsh") ==
        File(kHeader, {Shader(2, 5), Shader(9, 4), Shader(1, 3), Shader(3, 1)}));
}

TEST_CASE("A cache for another version is not shipped, and is replaced on the player's",
          "[graphics][shader_cache]") {
  TempDir dir;
  dir.Put("old.xsh", File(kOldHeader, {Shader(1, 3)}));
  dir.Put("user.xsh", File(kHeader, {Shader(2, 2)}));
  CHECK(SeedStorageFile(dir.path / "old.xsh", dir.path / "user.xsh", kShaders).result ==
        SeedResult::kStale);
  CHECK(dir.Get("user.xsh") == File(kHeader, {Shader(2, 2)}));

  dir.Put("shipped.xsh", File(kHeader, {Shader(1, 3)}));
  dir.Put("user.xsh", File(kOldHeader, {Shader(2, 2)}));
  CHECK(SeedStorageFile(dir.path / "shipped.xsh", dir.path / "user.xsh", kShaders).result ==
        SeedResult::kCopied);
  CHECK(dir.Get("user.xsh") == File(kHeader, {Shader(1, 3)}));
}

TEST_CASE("Pipeline descriptions merge by their hash, damaged ones dropped",
          "[graphics][shader_cache]") {
  TempDir dir;
  const uint8_t header[] = {'X', 'E', 'P', 'S', 'D', 'X', 'R', 'T', 1, 2, 3, 4};
  const StorageFormat pipelines{header, 32};
  Bytes damaged = Pipeline(7);
  damaged[20] ^= 0xFF;
  dir.Put("shipped.xpso", File(header, {Pipeline(1), Pipeline(2), damaged, Pipeline(3)}));
  dir.Put("user.xpso", File(header, {Pipeline(2)}));
  const auto outcome =
      SeedStorageFile(dir.path / "shipped.xpso", dir.path / "user.xpso", pipelines);
  CHECK(outcome.result == SeedResult::kMerged);

  CHECK(outcome.added == 1);
  CHECK(dir.Get("user.xpso") == File(header, {Pipeline(2), Pipeline(1)}));
}
