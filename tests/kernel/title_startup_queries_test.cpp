/**
 * @file        title_startup_queries_test.cpp
 * @brief       Content package paths, volume dismount and system link version status
 *
 * Legends resolves a content package path and opens it, formats the cache
 * partition and dismounts it, and asks for the system link broadcast version
 * status while it starts (research/kernel/title-startup-queries.md).
 *
 * @copyright   Copyright (c) 2026 ReXGlue contributors
 * @license     BSD 3-Clause License
 */

#include "kernel_fixture.h"

#include <cstring>

#include <rex/system/xam/user_profile.h>
#include <rex/types.h>

namespace rex::kernel::xam {
u32 XamContentResolve_entry(u32 user_index, mapped_void content_data_ptr, mapped_void buffer_ptr,
                            u32 buffer_size, u32 create_directory, u32 root_name_ptr,
                            u32 overlapped_ptr);
u32 NetDll_XNetGetBroadcastVersionStatus_entry(u32 caller, u32 reset);
}
namespace rex::kernel::xboxkrnl {
u32 IoDismountVolumeByFileHandle_entry(u32 handle);
}

namespace {

using namespace rex::testing;  // NOLINT
using rex::system::xam::ContentManager;
using rex::system::xam::ResolveContentPackageDevicePath;
using rex::system::xam::XCONTENT_DATA;

constexpr uint32_t kPathBufferSize = 260;

struct GuestResolve {
  uint32_t content_data;
  uint32_t buffer;
};

GuestResolve AllocateResolve(const XCONTENT_DATA& data) {
  auto* memory = Kernel()->memory();
  GuestResolve guest{memory->SystemHeapAlloc(sizeof(XCONTENT_DATA)),
                     memory->SystemHeapAlloc(kPathBufferSize)};
  REQUIRE(guest.content_data);
  REQUIRE(guest.buffer);
  *memory->TranslateVirtual<XCONTENT_DATA*>(guest.content_data) = data;
  std::memset(memory->TranslateVirtual(guest.buffer), 0xCC, kPathBufferSize);
  return guest;
}

uint32_t Resolve(uint32_t user_index, const GuestResolve& guest, uint32_t buffer_size,
                 uint32_t root_name = 0) {
  auto* memory = Kernel()->memory();
  return rex::kernel::xam::XamContentResolve_entry(
      user_index, mapped_void(memory->TranslateVirtual(guest.content_data), guest.content_data),
      mapped_void(memory->TranslateVirtual(guest.buffer), guest.buffer), buffer_size, 0, root_name,
      0);
}

std::string GuestString(uint32_t address) {
  return Kernel()->memory()->TranslateVirtual<const char*>(address);
}

}

TEST_CASE("Content package device paths follow the console content layout", "[kernel][content]") {
  auto save = SaveData("SLOT1");
  CHECK(ResolveContentPackageDevicePath(kXuid, kTitleId, save) ==
        "\\Device\\Harddisk0\\Partition1\\Content\\E000000012345678\\4D5307E6\\00000001\\SLOT1");

  auto disc = SaveData("DISCPACK");
  disc.device_id = 2;
  disc.content_type = XContentType::kMarketplaceContent;
  CHECK(ResolveContentPackageDevicePath(0, kTitleId, disc) ==
        "D:\\content\\0000000000000000\\4D5307E6\\00000002\\DISCPACK");

  auto unknown = SaveData("SLOT1");
  unknown.device_id = 3;
  CHECK_FALSE(ResolveContentPackageDevicePath(kXuid, kTitleId, unknown).has_value());
}

TEST_CASE("XamContentResolve writes the package path for the signed-in player's save",
          "[kernel][content]") {
  XCONTENT_DATA data = SaveData("SLOT1");
  auto guest = AllocateResolve(data);
  REQUIRE(Resolve(0, guest, kPathBufferSize) == X_ERROR_SUCCESS);
  CHECK(GuestString(guest.buffer) ==
        *ResolveContentPackageDevicePath(Kernel()->user_profile()->xuid(), Kernel()->title_id(),
                                         SaveData("SLOT1")));
}

TEST_CASE("XamContentResolve leaves the player out of downloadable content paths",
          "[kernel][content]") {
  XCONTENT_DATA data = SaveData("DLC1");
  data.content_type = XContentType::kMarketplaceContent;
  auto guest = AllocateResolve(data);
  REQUIRE(Resolve(0, guest, kPathBufferSize) == X_ERROR_SUCCESS);
  CHECK(GuestString(guest.buffer).find("\\0000000000000000\\") != std::string::npos);
}

TEST_CASE("XamContentResolve truncates to the caller's buffer", "[kernel][content]") {
  XCONTENT_DATA data = SaveData("SLOT1");
  auto guest = AllocateResolve(data);
  REQUIRE(Resolve(0, guest, 16) == X_ERROR_SUCCESS);
  CHECK(GuestString(guest.buffer) == "\\Device\\Harddis");
}

TEST_CASE("XamContentResolve rejects a root name and an unknown device", "[kernel][content]") {
  XCONTENT_DATA data = SaveData("SLOT1");
  auto guest = AllocateResolve(data);
  CHECK(Resolve(0, guest, kPathBufferSize, guest.buffer) == X_ERROR_INVALID_PARAMETER);

  data.device_id = 3;
  auto unknown = AllocateResolve(data);
  CHECK(Resolve(0, unknown, kPathBufferSize) == X_ERROR_INVALID_PARAMETER);
  CHECK(Resolve(0, unknown, 0) == X_ERROR_INVALID_PARAMETER);
}

TEST_CASE("Dismounting a volume needs an open file handle", "[kernel][io]") {
  KernelState* kernel = Kernel();
  CHECK(rex::kernel::xboxkrnl::IoDismountVolumeByFileHandle_entry(0xF8FFFFF0) ==
        X_STATUS_INVALID_HANDLE);

  TempDir root("rex_dismount");
  ContentManager content(kernel, root.path);
  const auto data = SaveData("SLOT1");
  REQUIRE(content.CreateContent("cache", kXuid, data) == X_ERROR_SUCCESS);
  auto file = OpenGuestFile(kernel, "cache", "volume.bin");
  CHECK(rex::kernel::xboxkrnl::IoDismountVolumeByFileHandle_entry(file->handle()) ==
        X_STATUS_SUCCESS);
  file->ReleaseHandle();
  file.reset();
  CHECK(content.CloseContent("cache") == X_ERROR_SUCCESS);
}

TEST_CASE("No other game versions are seen on system link", "[kernel][net]") {
  CHECK(rex::kernel::xam::NetDll_XNetGetBroadcastVersionStatus_entry(1, 0) == 0);
  CHECK(rex::kernel::xam::NetDll_XNetGetBroadcastVersionStatus_entry(1, 1) == 0);
}
