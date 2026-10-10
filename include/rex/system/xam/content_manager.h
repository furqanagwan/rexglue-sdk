/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <memory>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>
#include <rex/math.h>
#include <rex/memory.h>
#include <rex/string/key.h>
#include <rex/string.h>
#include <rex/system/xcontent.h>
#include <rex/system/xtypes.h>
#include <rex/thread/mutex.h>

namespace rex {
namespace system {
class KernelState;
}
}

namespace rex {
namespace system {
namespace xam {

constexpr uint32_t kCurrentlyRunningTitleId = 0xFFFFFFFF;

struct XCONTENT_DATA {
  be<uint32_t> device_id;
  be<XContentType> content_type;
  union {
    uint16_t uint[128];
    char16_t chars[128];
  } display_name_raw;

  char file_name_raw[42];

  uint8_t padding[2];

  bool operator==(const XCONTENT_DATA& other) const {
    return device_id == other.device_id && content_type == other.content_type &&
           file_name() == other.file_name();
  }

  std::u16string display_name() const {
    return memory::load_and_swap<std::u16string>(display_name_raw.uint);
  }

  std::string file_name() const {
    std::string value;
    value.assign(file_name_raw, std::min(strlen(file_name_raw), countof(file_name_raw)));
    return value;
  }

  void set_display_name(const std::u16string_view value) {
    std::fill_n(display_name_raw.chars, countof(display_name_raw.chars), 0);
    rex::string::copy_and_swap_truncating(display_name_raw.chars, value,
                                          countof(display_name_raw.chars));
  }

  void set_file_name(const std::string_view value) {
    std::fill_n(file_name_raw, countof(file_name_raw), 0);
    rex::string::copy_unterminated(file_name_raw, value, rex::countof(file_name_raw));

    padding[0] = padding[1] = 0;
  }
};
static_assert_size(XCONTENT_DATA, 0x134);

struct XCONTENT_AGGREGATE_DATA : XCONTENT_DATA {
  be<uint64_t> xuid;
  be<uint32_t> title_id;

  XCONTENT_AGGREGATE_DATA() = default;
  XCONTENT_AGGREGATE_DATA(const XCONTENT_DATA& other) {
    device_id = other.device_id;
    content_type = other.content_type;
    set_display_name(other.display_name());
    set_file_name(other.file_name());
    padding[0] = padding[1] = 0;
    xuid = 0;
    title_id = kCurrentlyRunningTitleId;
  }

  bool operator==(const XCONTENT_AGGREGATE_DATA& other) const {
    return device_id == other.device_id && title_id == other.title_id &&
           content_type == other.content_type && file_name() == other.file_name();
  }
};
static_assert_size(XCONTENT_AGGREGATE_DATA, 0x148);

class ContentPackage {
 public:
  ContentPackage(KernelState* kernel_state, const std::string_view root_name, uint64_t xuid,
                 const XCONTENT_AGGREGATE_DATA& data, const std::filesystem::path& package_path);
  ~ContentPackage();

  void LoadPackageLicenseMask(const std::filesystem::path header_path);

  const XCONTENT_AGGREGATE_DATA& GetPackageContentData() const { return content_data_; }

  const std::filesystem::path& package_path() const { return package_path_; }

  uint32_t GetPackageLicense() const { return license_; }

  uint64_t xuid() const { return xuid_; }

 private:
  KernelState* kernel_state_;
  std::string root_name_;
  std::string device_path_;
  std::filesystem::path package_path_;
  uint64_t xuid_ = 0;
  XCONTENT_AGGREGATE_DATA content_data_;
  uint32_t license_ = 0;
};

class ContentManager {
 public:
  ContentManager(KernelState* kernel_state, const std::filesystem::path& root_path);
  ~ContentManager();

  std::vector<XCONTENT_AGGREGATE_DATA> ListContent(uint32_t device_id, uint64_t xuid,
                                                   XContentType content_type,
                                                   uint32_t title_id = -1);

  std::unique_ptr<ContentPackage> ResolvePackage(const std::string_view root_name, uint64_t xuid,
                                                 const XCONTENT_AGGREGATE_DATA& data);

  bool ContentExists(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data);
  X_RESULT CreateContent(const std::string_view root_name, uint64_t xuid,
                         const XCONTENT_AGGREGATE_DATA& data);
  X_RESULT OpenContent(const std::string_view root_name, uint64_t xuid,
                       const XCONTENT_AGGREGATE_DATA& data, uint32_t& content_license);
  X_RESULT CloseContent(const std::string_view root_name);

  X_RESULT FlushContent(const std::string_view root_name);
  X_RESULT GetContentThumbnail(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data,
                               std::vector<uint8_t>* buffer);
  X_RESULT SetContentThumbnail(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data,
                               std::vector<uint8_t> buffer);
  X_RESULT DeleteContent(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data);
  X_RESULT UnmountContent(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data);
  X_RESULT UnmountAndDeleteContent(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data);

  X_RESULT WriteContentHeaderFile(uint64_t xuid, XCONTENT_AGGREGATE_DATA data,
                                  uint32_t license_mask = 0);
  X_RESULT ReadContentHeaderFile(const std::string_view file_name, uint64_t xuid, uint32_t title_id,
                                 XContentType content_type, XCONTENT_AGGREGATE_DATA& data) const;

  std::filesystem::path ResolveGameUserContentPath();

  std::filesystem::path GetPackagePath(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data) {
    return ResolvePackagePath(xuid, data);
  }
  bool IsContentOpen(const XCONTENT_AGGREGATE_DATA& data) const;
  void CloseOpenedFilesFromContent(const std::string_view root_name);

  std::filesystem::path GetOpenPackagePath(const std::string_view root_name) const;

  X_RESULT InstallContent(const std::filesystem::path& package_path);

 private:
  std::filesystem::path ResolvePackageRoot(uint64_t xuid, XContentType content_type,
                                           uint32_t title_id = -1);
  std::filesystem::path ResolvePackagePath(uint64_t xuid, const XCONTENT_AGGREGATE_DATA& data);
  std::filesystem::path ResolvePackageHeaderPath(const std::string_view file_name, uint64_t xuid,
                                                 uint32_t title_id,
                                                 XContentType content_type) const;

  std::unordered_map<string::string_key_case, ContentPackage*,
                     string::string_key_case::Hash>::iterator
  FindOpenPackageByData(const XCONTENT_AGGREGATE_DATA& data);
  ContentPackage* DetachPackage(std::unordered_map<string::string_key_case, ContentPackage*,
                                                   string::string_key_case::Hash>::iterator it);

  KernelState* kernel_state_;
  std::filesystem::path root_path_;

  rex::thread::global_critical_region global_critical_region_;
  std::unordered_map<string::string_key_case, ContentPackage*, string::string_key_case::Hash>
      open_packages_;
};

}
}
}
