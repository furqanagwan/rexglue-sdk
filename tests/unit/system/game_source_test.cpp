// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>
#include <windows.h>
#include <fstream>
#include <array>
#include <rex/hash.h>
#include <rex/system/game_source.h>
#include <rex/filesystem.h>
#include <rex/runtime.h>
#include <rex/filesystem/file.h>

using rex::X_STATUS;
namespace {
std::vector<uint8_t> SourceXex() {
  std::vector<uint8_t> bytes(128);
  std::memcpy(bytes.data(), "XEX2", 4);
  bytes[23] = 1;  // One optional header.
  bytes[25] = 4;
  bytes[27] = 6;  // XEX_HEADER_EXECUTION_INFO.
  bytes[31] = 32;
  bytes[44] = 0x12;
  bytes[45] = 0x34;
  bytes[46] = 0x56;
  bytes[47] = 0x78;
  return bytes;
}
std::vector<uint8_t> SourceIso() {
  std::vector<uint8_t> bytes(36 * 2048);
  auto put = [&bytes](size_t offset, uint32_t value) {
    for (int i = 0; i < 4; ++i)
      bytes[offset + i] = uint8_t(value >> (8 * i));
  };
  std::memcpy(bytes.data() + 32 * 2048, "MICROSOFT*XBOX*MEDIA", 20);
  std::memcpy(bytes.data() + 33 * 2048 - 20, "MICROSOFT*XBOX*MEDIA", 20);
  put(32 * 2048 + 20, 33);
  put(32 * 2048 + 24, 32);
  put(33 * 2048 + 4, 35);
  const auto xex = SourceXex();
  put(33 * 2048 + 8, uint32_t(xex.size()));
  bytes[33 * 2048 + 13] = 11;
  std::memcpy(bytes.data() + 33 * 2048 + 14, "default.xex", 11);
  std::memcpy(bytes.data() + 35 * 2048, xex.data(), xex.size());
  return bytes;
}
}  // namespace

TEST_CASE("Game source extraction commits a matching folder and preserves existing data",
          "[game_source][disc]") {
  const auto root = std::filesystem::temp_directory_path() /
                    ("rex-source-extraction-test-" + std::to_string(GetCurrentProcessId()));
  REQUIRE_FALSE(std::filesystem::exists(root));
  std::filesystem::create_directory(root);
  struct Clean {
    std::filesystem::path root;
    ~Clean() {
      std::error_code ec;
      std::filesystem::remove_all(root, ec);
    }
  } clean{root};
  const auto image = SourceIso();
  {
    std::ofstream output(root / "source.iso", std::ios::binary);
    output.write(reinterpret_cast<const char*>(image.data()), image.size());
  }
  auto source = rex::system::InspectGameSource(root / "source.iso");
  REQUIRE(source);
  const auto expected = source.identity;
  {
    rex::Runtime runtime(root / "source.iso", root / "users", {}, root / "cache");
    REQUIRE(runtime.Setup(rex::RuntimeConfig{.tool_mode = true}) == X_STATUS_SUCCESS);
    auto* game = runtime.file_system()->ResolvePath("game:\\default.xex");
    auto* drive = runtime.file_system()->ResolvePath("d:\\default.xex");
    REQUIRE(game);
    CHECK(game == drive);
    rex::filesystem::File* file = nullptr;
    REQUIRE(game->Open(rex::filesystem::FileAccess::kGenericRead, &file) == X_STATUS_SUCCESS);
    struct Close {
      rex::filesystem::File* file;
      ~Close() { file->Destroy(); }
    } close{file};
    std::array<uint8_t, 4> magic{};
    size_t read = 0;
    CHECK(file->ReadSync(magic, 0, &read) == X_STATUS_SUCCESS);
    CHECK(read == 4);
    CHECK(std::string(magic.begin(), magic.end()) == "XEX2");
  }
  {
    std::ofstream keep(root / "keep.txt");
    keep << "existing saves";
  }
  const auto target = root / "installed";
  uint64_t done = 0;
  bool cancel = false;
  bool cancel_after_copy = false;
  bool fail_read = false;
  SECTION("Successful copy") {}
  SECTION("Cancellation before copying") {
    cancel = true;
  }
  SECTION("Cancellation after copying") {
    cancel_after_copy = true;
  }
  SECTION("Source disappears during extraction") {
    fail_read = true;
  }
  auto copy = rex::system::ExtractGameSource(
      root / "source.iso", target, expected,
      [&](uint64_t copied, uint64_t total) {
        CHECK(total == SourceXex().size());
        done = copied;
        if (cancel_after_copy && copied)
          cancel = true;
        if (fail_read && !copied) {
          auto writer = rex::filesystem::FileHandle::OpenExisting(
              root / "source.iso", rex::filesystem::FileAccess::kGenericWrite);
          REQUIRE(writer);
          REQUIRE(writer->SetLength(35 * 2048));
        }
      },
      [&] { return cancel; });
  if (cancel) {
    CHECK(copy.cancelled);
    CHECK_FALSE(std::filesystem::exists(target));
  } else if (fail_read) {
    CHECK_FALSE(copy);
    CHECK_FALSE(copy.error.empty());
    CHECK_FALSE(std::filesystem::exists(target));
  } else {
    REQUIRE(copy);
    CHECK(done == SourceXex().size());
    CHECK(rex::system::InspectGameSource(target, "default.xex", expected));
    const auto before = rex::hash_file(target / "default.xex");
    CHECK_FALSE(rex::system::ExtractGameSource(root / "source.iso", target, expected));
    CHECK(rex::hash_file(target / "default.xex") == before);
  }
  std::ifstream keep(root / "keep.txt");
  std::string existing;
  std::getline(keep, existing);
  CHECK(existing == "existing saves");
  for (const auto& file : std::filesystem::directory_iterator(root))
    CHECK(file.path().filename().string().find(".partial-") == std::string::npos);
}

TEST_CASE("Game source identity checks the original XEX header and full-file checksum",
          "[game_source]") {
  // Relative paths need the working directory's volume. Hosted Windows runners
  // may keep TEMP on C: and the CTest working directory on D:.
  const auto root = std::filesystem::current_path() /
                    ("rex-source-identity-test-" + std::to_string(GetCurrentProcessId()));
  REQUIRE_FALSE(std::filesystem::exists(root));
  std::filesystem::create_directories(root);
  struct Clean {
    std::filesystem::path root;
    ~Clean() {
      std::error_code ec;
      std::filesystem::remove(root / "default.xex", ec);
      std::filesystem::remove(root, ec);
    }
  } clean{root};
  auto xex = SourceXex();
  {
    std::ofstream file(root / "default.xex", std::ios::binary);
    file.write(reinterpret_cast<const char*>(xex.data()), xex.size());
  }
  auto source = rex::system::InspectGameSource(root);
  REQUIRE(source);
  CHECK(source.identity.title_id == 0x12345678);
  CHECK(source.source_path == std::filesystem::absolute(root));
  auto relative = rex::system::InspectGameSource(std::filesystem::relative(root));
  REQUIRE(relative);
  CHECK(relative.source_path.is_absolute());
  CHECK(std::filesystem::equivalent(relative.source_path, source.source_path));
  CHECK(source.identity.executable_checksum == rex::hash_file(root / "default.xex"));
  const auto expected = source.identity;
  REQUIRE(rex::system::InspectGameSource(root, "default.xex", expected));
  for (const auto* escaped : {"../default.xex", "..\\default.xex", "/default.xex", "C:/default.xex",
                              "folder/../default.xex", "default.xex/"}) {
    auto rejected = rex::system::InspectGameSource(root, escaped, expected);
    CHECK_FALSE(rejected);
    CHECK(rejected.error.find("relative") != std::string::npos);
  }
  auto cancelled =
      rex::system::InspectGameSource(root, "default.xex", expected, [] { return true; });
  CHECK_FALSE(cancelled);
  CHECK(cancelled.error.find("cancelled") != std::string::npos);
  auto wrong_title = expected;
  wrong_title.title_id = 0x87654321;
  auto mismatch = rex::system::InspectGameSource(root, "default.xex", wrong_title);
  CHECK_FALSE(mismatch);
  CHECK(mismatch.error.find("87654321") != std::string::npos);
  CHECK(mismatch.error.find("12345678") != std::string::npos);
  xex.back() ^= 1;
  {
    std::ofstream file(root / "default.xex", std::ios::binary);
    file.write(reinterpret_cast<const char*>(xex.data()), xex.size());
  }
  CHECK_FALSE(rex::system::InspectGameSource(root, "default.xex", expected));
  CHECK_FALSE(rex::system::InspectGameSource(root, "missing.xex"));
  CHECK_FALSE(rex::system::InspectGameSource(root / "missing"));
}

TEST_CASE("Game source XEX header inspection bounds optional headers", "[game_source]") {
  auto bytes = SourceXex();
  CHECK(rex::system::XexSourceTitleId(bytes) == 0x12345678);
  SECTION("Short header") {
    bytes.resize(23);
  }
  SECTION("Too many headers") {
    bytes[20] = 0xFF;
  }
  SECTION("Execution info outside buffer") {
    bytes[28] = 0xFF;
  }
  SECTION("Unsupported magic") {
    bytes[3] = '1';
  }
  SECTION("Missing execution info") {
    bytes[27] = 0;
  }
  CHECK(rex::system::XexSourceTitleId(bytes) == 0);
}
