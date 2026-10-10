// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>
#include <windows.h>
#include <fstream>
#include <iterator>
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
  bytes[23] = 1;
  bytes[25] = 4;
  bytes[27] = 6;
  bytes[31] = 32;
  bytes[44] = 0x12;
  bytes[45] = 0x34;
  bytes[46] = 0x56;
  bytes[47] = 0x78;
  return bytes;
}

std::vector<uint8_t> NamedXex(std::string_view title) {
  constexpr uint32_t kBase = 0x82000000, kHeaderSize = 0x400, kResource = 0x10;
  std::vector<uint8_t> xdbf;
  auto be = [](std::vector<uint8_t>& out, uint64_t value, int bytes) {
    for (int i = bytes - 1; i >= 0; --i)
      out.push_back(uint8_t(value >> (8 * i)));
  };
  std::vector<uint8_t> xstr;
  be(xstr, 0x58535452, 4);
  be(xstr, 1, 4);
  be(xstr, 0, 4);
  be(xstr, 1, 2);
  be(xstr, 0x8000, 2);
  be(xstr, title.size(), 2);
  xstr.insert(xstr.end(), title.begin(), title.end());
  be(xdbf, 0x58444246, 4);
  be(xdbf, 1, 4);
  be(xdbf, 1, 4);
  be(xdbf, 1, 4);
  be(xdbf, 0, 4);
  be(xdbf, 0, 4);
  be(xdbf, 3, 2);
  be(xdbf, 1, 8);
  be(xdbf, 0, 4);
  be(xdbf, xstr.size(), 4);
  xdbf.insert(xdbf.end(), xstr.begin(), xstr.end());

  std::vector<uint8_t> bytes(kHeaderSize);
  auto put = [&bytes](size_t offset, uint32_t value) {
    for (int i = 0; i < 4; ++i)
      bytes[offset + i] = uint8_t(value >> (24 - 8 * i));
  };
  std::memcpy(bytes.data(), "XEX2", 4);
  put(0x08, kHeaderSize);
  put(0x10, 0x200);
  put(0x14, 3);
  put(0x18, 0x00040006);
  put(0x1C, 0x100);
  put(0x20, 0x000002FF);
  put(0x24, 0x140);
  put(0x28, 0x000003FF);
  put(0x2C, 0x180);
  put(0x100 + 12, 0x12345678);
  put(0x140, 20);
  std::memcpy(bytes.data() + 0x144, "12345678", 8);
  put(0x14C, kBase + kResource);
  put(0x150, uint32_t(xdbf.size()));
  put(0x180, 8);
  put(0x200 + 4, kResource + uint32_t(xdbf.size()));
  put(0x200 + 0x110, kBase);
  bytes.resize(kHeaderSize + kResource);
  bytes.insert(bytes.end(), xdbf.begin(), xdbf.end());
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
}

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

TEST_CASE("Game source XEX title names come from the image's XDBF resource", "[game_source]") {
  auto bytes = NamedXex("Test Game\xE2\x84\xA2");
  CHECK(rex::system::XexTitleName(bytes) == "Test Game\xE2\x84\xA2");
  CHECK(rex::system::XexTitleName(SourceXex()).empty());
  SECTION("Resource outside the image") {
    bytes[0x14F] = 0xFF;
  }
  SECTION("Truncated image") {
    bytes.resize(0x420);
  }
  SECTION("String longer than its table") {
    bytes[bytes.size() - 14] = 0xFF;
  }
  SECTION("Resource names another title") {
    bytes[0x144] = '9';
  }
  SECTION("Unsupported compression") {
    bytes[0x187] = 3;
  }
  SECTION("No XDBF magic") {
    bytes[0x410] = 'Y';
  }
  CHECK(rex::system::XexTitleName(bytes).empty());
}

TEST_CASE("A source holding another game names both games", "[game_source]") {
  const auto root = std::filesystem::current_path() /
                    ("rex-source-name-test-" + std::to_string(GetCurrentProcessId()));
  REQUIRE_FALSE(std::filesystem::exists(root));
  std::filesystem::create_directories(root);
  struct Clean {
    std::filesystem::path root;
    ~Clean() {
      std::error_code ec;
      std::filesystem::remove_all(root, ec);
    }
  } clean{root};
  const auto xex = NamedXex("Test Game\xE2\x84\xA2");
  {
    std::ofstream file(root / "default.xex", std::ios::binary);
    file.write(reinterpret_cast<const char*>(xex.data()), xex.size());
  }
  rex::system::GameSourceIdentity expected{0x41560817, "", "007: Quantum of Solace"};
  auto mismatch = rex::system::InspectGameSource(root, "default.xex", expected);
  CHECK_FALSE(mismatch);
  CHECK(mismatch.identity.title_name == "Test Game");
  CHECK(mismatch.error ==
        "This is Test Game (12345678). This build is for 007: Quantum of Solace (41560817).");

  expected.title_name.clear();
  CHECK(rex::system::InspectGameSource(root, "default.xex", expected).error ==
        "This is Test Game (12345678). This build is for title 41560817.");
}

TEST_CASE("A retail XEX's title name decodes from its encrypted image", "[game_source][local]") {
  const char* path = std::getenv("REXGLUE_TITLE_XEX");
  if (!path || !*path)
    SKIP("REXGLUE_TITLE_XEX is not set");
  std::ifstream file(std::filesystem::path(path), std::ios::binary);
  const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(file)), {});
  const auto name = rex::system::XexTitleName(bytes);
  INFO(path);
  CHECK_FALSE(name.empty());
  WARN("Title name: " << name);
}
