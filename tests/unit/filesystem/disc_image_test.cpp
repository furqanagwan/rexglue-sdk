// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>
#include <windows.h>

#include <array>
#include <cstring>
#include <fstream>
#include <future>
#include <thread>
#include <rex/filesystem/devices/disc_image_device.h>
#include <rex/filesystem/file.h>
#include <rex/filesystem/devices/optical_disc_reader.h>

using namespace rex::filesystem;
using rex::X_STATUS;
namespace {
constexpr size_t kSector = 2048;
constexpr size_t kRoot = 33 * kSector;
constexpr size_t kPayload = 35 * kSector;
void Put32(std::vector<uint8_t>& bytes, size_t offset, uint32_t value) {
  for (int i = 0; i < 4; ++i)
    bytes[offset + i] = uint8_t(value >> (8 * i));
}

std::vector<uint8_t> Image() {
  std::vector<uint8_t> bytes(36 * kSector);
  std::memcpy(bytes.data() + 32 * kSector, "MICROSOFT*XBOX*MEDIA", 20);
  std::memcpy(bytes.data() + 33 * kSector - 20, "MICROSOFT*XBOX*MEDIA", 20);
  Put32(bytes, 32 * kSector + 20, 33);
  Put32(bytes, 32 * kSector + 24, 32);
  Put32(bytes, kRoot + 4, 35);
  Put32(bytes, kRoot + 8, 7);
  bytes[kRoot + 13] = 11;
  std::memcpy(bytes.data() + kRoot + 14, "default.xex", 11);
  std::memcpy(bytes.data() + kPayload, "payload", 7);
  return bytes;
}
class Reader : public FileHandle {
 public:
  explicit Reader(std::vector<uint8_t> data) : FileHandle({}), bytes(std::move(data)) {}
  bool Read(size_t offset, void* buffer, size_t count, size_t* read) override {
    *read = 0;
    if (offset >= fail_at || offset > bytes.size() || count > bytes.size() - offset)
      return false;
    if (short_reads && count)
      --count;
    std::memcpy(buffer, bytes.data() + offset, count);
    *read = count;
    return true;
  }
  bool Write(size_t, const void*, size_t, size_t*) override { return false; }
  bool SetLength(size_t) override { return false; }
  bool Flush() override { return false; }
  std::vector<uint8_t> bytes;
  size_t fail_at = SIZE_MAX;
  bool short_reads = false;
};
struct Mounted {
  explicit Mounted(std::vector<uint8_t> bytes = Image()) {
    const auto size = bytes.size();
    auto source = std::make_unique<Reader>(std::move(bytes));
    reader = source.get();
    disc = std::make_unique<DiscImageDevice>("disc:", std::move(source), size);
  }
  Reader* reader;
  std::unique_ptr<DiscImageDevice> disc;
};
struct FileGuard {
  explicit FileGuard(Entry* entry) {
    REQUIRE(entry);
    REQUIRE(entry->Open(FileAccess::kGenericRead, &file) == X_STATUS_SUCCESS);
  }
  ~FileGuard() { file->Destroy(); }
  File* file = nullptr;
};
}

TEST_CASE("XDVDFS file reads and owned snapshots preserve read-only semantics",
          "[filesystem][disc]") {
  Mounted mount;
  REQUIRE(mount.disc->Initialize());
  CHECK(mount.disc->file_count() == 1);
  CHECK(mount.disc->total_file_size() == 7);
  auto* entry = mount.disc->ResolvePath("DEFAULT.XEX");
  REQUIRE(entry);
  FileGuard file(entry);
  std::array<uint8_t, 12> buffer{};
  size_t read = 99;
  REQUIRE(file.file->ReadSync(buffer, 2, &read) == X_STATUS_SUCCESS);
  CHECK(read == 5);
  CHECK(std::string(buffer.begin(), buffer.begin() + read) == "yload");
  CHECK(file.file->ReadSync(buffer, 7, &read) == X_STATUS_END_OF_FILE);
  CHECK(read == 0);
  CHECK(file.file->ReadSync({}, SIZE_MAX, &read) == X_STATUS_SUCCESS);
  auto snapshot = entry->OpenMapped(rex::memory::MappedMemory::Mode::kRead, 2, 99);
  REQUIRE(snapshot);
  CHECK(snapshot->size() == 5);
  CHECK(std::string(reinterpret_cast<char*>(snapshot->data()), 5) == "yload");
  CHECK_FALSE(entry->OpenMapped(rex::memory::MappedMemory::Mode::kRead, 8));
  CHECK_FALSE(entry->OpenMapped(rex::memory::MappedMemory::Mode::kReadWrite));
  File* writable = nullptr;
  CHECK(entry->Open(FileAccess::kGenericWrite, &writable) == X_STATUS_ACCESS_DENIED);
  CHECK(writable == nullptr);
  mount.reader->fail_at = 0;
  CHECK(std::string(reinterpret_cast<char*>(snapshot->data()), 5) == "yload");
}

TEST_CASE("XDVDFS reports media failure and short reads on an already-open file",
          "[filesystem][disc]") {
  Mounted mount;
  REQUIRE(mount.disc->Initialize());
  auto* entry = mount.disc->ResolvePath("default.xex");
  FileGuard file(entry);
  SECTION("Media fails") {
    mount.reader->fail_at = kPayload;
  }
  SECTION("Host read is short") {
    mount.reader->short_reads = true;
  }
  std::array<uint8_t, 7> bytes{};
  size_t read = 99;
  CHECK(file.file->ReadSync(bytes, 0, &read) == X_STATUS_UNEXPECTED_IO_ERROR);
  CHECK(read == 0);
  CHECK_FALSE(entry->OpenMapped(rex::memory::MappedMemory::Mode::kRead));
  mount.reader->fail_at = SIZE_MAX;
  mount.reader->short_reads = false;
  REQUIRE(file.file->ReadSync(bytes, 0, &read) == X_STATUS_SUCCESS);
  CHECK(read == 7);
}

TEST_CASE("XDVDFS rejects truncated headers and invalid directory trees", "[filesystem][disc]") {
  auto bytes = Image();
  SECTION("Short header") {
    bytes.resize(32 * kSector + 20);
  }
  SECTION("Missing trailing magic") {
    bytes[33 * kSector - 1] = 0;
  }
  SECTION("Directory range outside image") {
    Put32(bytes, 32 * kSector + 20, UINT32_MAX);
  }
  SECTION("Short directory node") {
    Put32(bytes, 32 * kSector + 24, 13);
  }
  SECTION("Name beyond directory") {
    bytes[kRoot + 13] = 255;
  }
  SECTION("Traversal name") {
    bytes[kRoot + 13] = 2;
    std::memcpy(bytes.data() + kRoot + 14, "..", 2);
  }
  SECTION("Embedded path separator") {
    bytes[kRoot + 15] = '\\';
  }
  SECTION("File range outside image") {
    Put32(bytes, kRoot + 8, UINT32_MAX);
  }
  SECTION("Child ordinal outside table") {
    bytes[kRoot] = 255;
  }
  SECTION("Cyclic directory") {
    Put32(bytes, kRoot + 4, 33);
    Put32(bytes, kRoot + 8, 32);
    bytes[kRoot + 12] = kFileAttributeDirectory;
  }
  SECTION("Cyclic entry tree") {
    Put32(bytes, 32 * kSector + 24, 64);
    bytes[kRoot] = 8;
    bytes[kRoot + 32] = 8;
  }
  Mounted mount(std::move(bytes));
  CHECK_FALSE(mount.disc->Initialize());
  CHECK(mount.disc->ResolvePath("") == nullptr);
}

TEST_CASE("XDVDFS physical file truncation returns an error without mapped-file faults",
          "[filesystem][disc]") {
  const auto path = std::filesystem::temp_directory_path() /
                    ("rex-disc-read-test-" + std::to_string(GetCurrentProcessId()) + ".iso");
  struct Cleanup {
    std::filesystem::path path;
    ~Cleanup() {
      std::error_code ec;
      std::filesystem::remove(path, ec);
    }
  } cleanup{path};
  const auto image = Image();
  {
    std::ofstream output(path, std::ios::binary);
    output.write(reinterpret_cast<const char*>(image.data()), image.size());
  }
  DiscImageDevice disc("disc:", path);
  REQUIRE(disc.Initialize());
  FileGuard file(disc.ResolvePath("default.xex"));
  auto writer = FileHandle::OpenExisting(path, FileAccess::kGenericWrite);
  REQUIRE(writer);
  REQUIRE(writer->SetLength(kPayload));
  std::array<uint8_t, 7> bytes{};
  size_t read = 99;
  CHECK(file.file->ReadSync(bytes, 0, &read) == X_STATUS_UNEXPECTED_IO_ERROR);
  CHECK(read == 0);
}

TEST_CASE("Optical reader satisfies sector alignment for unaligned guest reads",
          "[filesystem][disc]") {
  class SectorReader : public Reader {
   public:
    SectorReader() : Reader(Image()) {}
    bool Read(size_t offset, void* buffer, size_t size, size_t* read) override {
      CHECK(offset % kSector == 0);
      CHECK(size % kSector == 0);
      CHECK(reinterpret_cast<uintptr_t>(buffer) % kSector == 0);
      return Reader::Read(offset, buffer, size, read);
    }
  };
  auto source = std::make_unique<SectorReader>();
  auto* fake = source.get();
  auto reader = MakeSectorAlignedDiscReader(std::move(source), kSector, 36 * kSector);
  REQUIRE(reader);
  std::array<uint8_t, 5> buffer{};
  size_t read = 99;
  REQUIRE(reader->Read(kPayload + 2, buffer.data(), buffer.size(), &read));
  CHECK(read == 5);
  CHECK(std::string(buffer.begin(), buffer.end()) == "yload");
  fake->short_reads = true;
  CHECK_FALSE(reader->Read(kPayload + 2, buffer.data(), buffer.size(), &read));
  CHECK(read == 0);
  CHECK_FALSE(reader->Read(SIZE_MAX, buffer.data(), buffer.size(), &read));
  CHECK_FALSE(MakeSectorAlignedDiscReader(std::make_unique<Reader>(Image()), 3, 36 * kSector));
}

TEST_CASE("Optical path handling accepts only drive-letter devices", "[filesystem][disc]") {
  CHECK(IsOpticalDiscPath(L"\\\\.\\D:"));
  CHECK(IsOpticalDiscPath(L"\\\\.\\z:"));
  CHECK_FALSE(IsOpticalDiscPath(L"\\\\.\\PhysicalDrive0"));
  CHECK_FALSE(IsOpticalDiscPath(L"D:\\"));
  CHECK_FALSE(IsOpticalDiscPath(L"\\\\.\\D:\\file"));
  size_t size = 99;
  CHECK_FALSE(OpenOpticalDisc(L"\\\\.\\PhysicalDrive0", &size));
  CHECK(size == 0);
}

TEST_CASE("Disc recovery retains open files and serializes concurrent retries",
          "[filesystem][disc][media_recovery]") {
  Mounted mount;
  Mounted replacement;
  REQUIRE(mount.disc->Initialize());
  REQUIRE(replacement.disc->Initialize());
  FileGuard file(mount.disc->ResolvePath("default.xex"));
  mount.reader->fail_at = kPayload;
  int retries = 0;
  mount.disc->SetFailureHandler([&] {
    ++retries;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return mount.disc->ReconnectFrom(*replacement.disc);
  });
  auto read = [&] {
    std::array<uint8_t, 7> bytes{};
    size_t read = 0;
    const auto status = file.file->ReadSync(bytes, 0, &read);
    return status == X_STATUS_SUCCESS && read == 7 &&
           std::string(bytes.begin(), bytes.end()) == "payload";
  };
  auto first = std::async(std::launch::async, read);
  auto second = std::async(std::launch::async, read);
  CHECK(first.get());
  CHECK(second.get());
  CHECK(retries == 1);
}

TEST_CASE("Disc recovery refuses a replacement with different directory layout",
          "[filesystem][disc][media_recovery]") {
  Mounted mount;
  auto image = Image();
  Put32(image, kRoot + 8, 6);
  Mounted replacement(std::move(image));
  REQUIRE(mount.disc->Initialize());
  REQUIRE(replacement.disc->Initialize());
  CHECK_FALSE(mount.disc->ReconnectFrom(*replacement.disc));
}

TEST_CASE("A UI read returns an error while a guest worker waits for media",
          "[filesystem][disc][media_recovery]") {
  Mounted mount;
  Mounted replacement;
  REQUIRE(mount.disc->Initialize());
  REQUIRE(replacement.disc->Initialize());
  FileGuard file(mount.disc->ResolvePath("default.xex"));
  mount.reader->fail_at = kPayload;
  std::promise<void> prompted, released;
  auto prompt_ready = prompted.get_future();
  auto release = released.get_future().share();
  std::future<bool> guest, ui;
  struct ReleaseOnExit {
    std::promise<void>& released;
    bool done = false;
    void Release() {
      if (!done) {
        released.set_value();
        done = true;
      }
    }
    ~ReleaseOnExit() { Release(); }
  } guard{released};
  static thread_local bool ui_thread = false;
  mount.disc->SetFailureHandler(
      [&] {
        prompted.set_value();
        release.wait();
        return mount.disc->ReconnectFrom(*replacement.disc);
      },
      [] { return !ui_thread; });
  auto read = [&] {
    std::array<uint8_t, 7> bytes{};
    size_t count = 0;
    return file.file->ReadSync(bytes, 0, &count) == X_STATUS_SUCCESS;
  };
  guest = std::async(std::launch::async, read);
  REQUIRE(prompt_ready.wait_for(std::chrono::seconds(1)) == std::future_status::ready);
  ui = std::async(std::launch::async, [&] {
    ui_thread = true;
    return read();
  });
  REQUIRE(ui.wait_for(std::chrono::seconds(1)) == std::future_status::ready);
  CHECK_FALSE(ui.get());
  guard.Release();
  CHECK(guest.get());
}
