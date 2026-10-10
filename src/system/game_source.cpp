// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/system/game_source.h>

#include <array>
#include <chrono>
#include <fstream>
#include <fmt/format.h>
#include <rex/filesystem/devices/disc_image_device.h>
#include <rex/filesystem/devices/host_path_device.h>
#include <rex/filesystem/devices/optical_disc_reader.h>
#include <rex/filesystem/file.h>
#include <rex/hash.h>
#include <rex/logging.h>
#include <rex/system/util/xdbf_utils.h>

namespace rex::system {
uint32_t XexSourceTitleId(std::span<const uint8_t> bytes) {
  auto be32 = [&bytes](size_t offset) {
    return (uint32_t(bytes[offset]) << 24) | (uint32_t(bytes[offset + 1]) << 16) |
           (uint32_t(bytes[offset + 2]) << 8) | bytes[offset + 3];
  };
  if (bytes.size() < 24 || std::memcmp(bytes.data(), "XEX2", 4))
    return 0;
  const uint32_t headers = be32(20);
  if (headers > (bytes.size() - 24) / 8)
    return 0;
  for (uint32_t i = 0; i < headers; ++i) {
    if (be32(24 + i * 8) != 0x00040006)
      continue;
    const size_t offset = be32(28 + i * 8);
    if (offset > bytes.size() || bytes.size() - offset < 24)
      return 0;
    return be32(offset + 12);
  }
  return 0;
}

GameSourceResult InspectGameSource(const std::filesystem::path& path, std::string_view executable,
                                   const GameSourceIdentity& expected,
                                   const std::function<bool()>& cancelled) {
  GameSourceResult result;

  std::string guest_path(executable);
  std::replace(guest_path.begin(), guest_path.end(), '\\', '/');
  bool invalid_path = guest_path.empty() || guest_path.starts_with('/') ||
                      guest_path.find(':') != std::string::npos ||
                      guest_path.find('\0') != std::string::npos;
  for (size_t start = 0; start < guest_path.size();) {
    const auto end = guest_path.find('/', start);
    const auto part =
        std::string_view(guest_path)
            .substr(start, end == std::string::npos ? std::string::npos : end - start);
    invalid_path |= part.empty() || part == "." || part == "..";
    if (end == std::string::npos)
      break;
    start = end + 1;
  }
  if (invalid_path || guest_path.ends_with('/')) {
    result.error =
        "This game is set up incorrectly and can't be started from a disc (its executable path "
        "isn't relative).";
    return result;
  }
  if (cancelled && cancelled()) {
    result.error = "Cancelled.";
    return result;
  }
  std::error_code ec;
  const auto absolute = std::filesystem::absolute(path, ec);
  if (path.empty() || ec) {
    result.error = "Choose the game's disc, disc image or folder.";
    return result;
  }
  result.source_path = absolute.lexically_normal();
  if (std::filesystem::is_directory(absolute, ec)) {
    result.device = std::make_unique<filesystem::HostPathDevice>("source:", absolute, true);
  } else if (filesystem::IsOpticalDiscPath(absolute) ||
             std::filesystem::is_regular_file(absolute, ec)) {
    result.device = std::make_unique<filesystem::DiscImageDevice>("source:", absolute);
  } else {
    result.error = "The disc or file can't be found. Check that it's connected, and try again.";
    return result;
  }
  if (!result.device->Initialize()) {
    result.error = filesystem::IsOpticalDiscPath(absolute)
                       ? "Unable to read the disc. Make sure it's an Xbox 360 game disc. Most PC "
                         "drives can't read Xbox 360 discs."
                       : "This isn't an Xbox 360 game disc image, or it's damaged.";
    return result;
  }
  auto* entry = result.device->ResolvePath(guest_path);
  if (!entry || (entry->attributes() & filesystem::kFileAttributeDirectory)) {
    result.error = fmt::format("The game wasn't found here ({} is missing).", executable);
    return result;
  }

  if (entry->size() < 24 || entry->size() > 512 * 1024 * 1024) {
    result.error = "This isn't an Xbox 360 game.";
    return result;
  }
  filesystem::File* file = nullptr;
  if (XFAILED(entry->Open(filesystem::FileAccess::kGenericRead, &file))) {
    result.error =
        "Unable to read the game. Check that the disc or drive is connected, and try again.";
    return result;
  }
  struct Close {
    filesystem::File* file;
    ~Close() { file->Destroy(); }
  } close{file};
  const size_t header_size = std::min(entry->size(), size_t(1024 * 1024));
  std::vector<uint8_t> header(header_size);
  size_t read = 0;
  if (XFAILED(file->ReadSync(header, 0, &read)) || read != header.size()) {
    result.error =
        "Unable to read the game. Check that the disc or drive is connected, and try again.";
    return result;
  }
  result.identity.title_id = XexSourceTitleId(header);
  if (!result.identity.title_id) {
    result.error = "This isn't an Xbox 360 game.";
    return result;
  }
  auto state =
      std::unique_ptr<XXH3_state_t, decltype(&XXH3_freeState)>(XXH3_createState(), XXH3_freeState);
  if (!state || XXH3_128bits_reset(state.get()) == XXH_ERROR) {
    result.error =
        "Unable to read the game. Check that the disc or drive is connected, and try again.";
    return result;
  }

  const bool other_title = expected.title_id && expected.title_id != result.identity.title_id;
  std::vector<uint8_t> whole;
  if (other_title)
    whole.reserve(entry->size());
  std::array<uint8_t, 256 * 1024> chunk;
  for (size_t offset = 0; offset < entry->size();) {
    if (cancelled && cancelled()) {
      result.error = "Cancelled.";
      return result;
    }
    const auto count = std::min(chunk.size(), entry->size() - offset);
    if (XFAILED(file->ReadSync(std::span(chunk).first(count), offset, &read)) || read != count ||
        XXH3_128bits_update(state.get(), chunk.data(), count) == XXH_ERROR) {
      result.error =
          "Unable to read the game. Check that the disc or drive is connected, and try again.";
      return result;
    }
    if (other_title)
      whole.insert(whole.end(), chunk.begin(), chunk.begin() + count);
    offset += count;
  }
  const auto hash = XXH3_128bits_digest(state.get());
  result.identity.executable_checksum = fmt::format("{:016x}{:016x}", hash.high64, hash.low64);
  if (other_title) {
    result.identity.title_name = util::TitleDisplayName(XexTitleName(whole));
    REXLOG_WARN("Game source is title {:08X}; this build is for title {:08X}",
                result.identity.title_id, expected.title_id);
    const std::string found =
        result.identity.title_name.empty() ? "a different game" : result.identity.title_name;
    result.error =
        expected.title_name.empty()
            ? fmt::format("This is {}. Choose the disc for this game.", found)
            : fmt::format("This is {}. Choose the disc for {}.", found, expected.title_name);
  } else if (!expected.executable_checksum.empty() &&
             expected.executable_checksum != result.identity.executable_checksum) {
    result.error =
        "This version of the game isn't supported. It may be from another region or edition.";
  }
  return result;
}

GameSourceExtraction ExtractGameSource(const std::filesystem::path& image,
                                       const std::filesystem::path& destination,
                                       const GameSourceIdentity& expected,
                                       const std::function<void(uint64_t, uint64_t)>& progress,
                                       const std::function<bool()>& cancelled,
                                       std::string_view executable) {
  GameSourceExtraction result;
  auto source = InspectGameSource(image, executable, expected, cancelled);
  if (cancelled && cancelled()) {
    result.cancelled = true;
    return result;
  }
  if (!source) {
    result.error = source.error;
    return result;
  }
  auto* disc = dynamic_cast<filesystem::DiscImageDevice*>(source.device.get());
  if (!disc) {
    result.error = "Choose a disc image.";
    return result;
  }
  std::filesystem::path staging;
  bool owns_staging = false;
  auto cleanup = [&] {
    if (!owns_staging)
      return;
    std::error_code ec;

    const auto actual = std::filesystem::weakly_canonical(staging, ec);
    if (ec || std::filesystem::is_symlink(staging, ec))
      return;
    const auto parent = std::filesystem::weakly_canonical(staging.parent_path(), ec);
    if (!ec && actual == parent / staging.filename())
      std::filesystem::remove_all(actual, ec);
  };
  try {
    const auto target = std::filesystem::absolute(destination).lexically_normal();
    if (destination.empty() || std::filesystem::exists(target)) {
      result.error = "The game files can't be copied there because that folder already exists.";
      return result;
    }
    std::filesystem::create_directories(target.parent_path());
    staging = target.parent_path() /
              (target.filename().string() + ".partial-" +
               std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    if (!std::filesystem::create_directory(staging)) {
      result.error =
          "Unable to copy the game files. Check that there's enough free space, and try again.";
      return result;
    }
    owns_staging = true;
    struct Pending {
      const filesystem::Entry* entry;
      std::filesystem::path relative;
    };
    std::vector<Pending> pending;
    for (const auto& entry : disc->root()->children())
      pending.push_back({entry.get(), {}});
    uint64_t copied = 0;
    const uint64_t total = disc->total_file_size();
    if (progress)
      progress(copied, total);
    std::array<uint8_t, 256 * 1024> buffer;
    while (!pending.empty()) {
      if (cancelled && cancelled()) {
        result.cancelled = true;
        cleanup();
        return result;
      }
      auto item = std::move(pending.back());
      pending.pop_back();
      const auto& name = item.entry->name();
      const auto upper = rex::string::utf8_upper_ascii(name.substr(0, name.find('.')));
      const bool reserved =
          upper == "CON" || upper == "PRN" || upper == "AUX" || upper == "NUL" ||
          (upper.size() == 4 && (upper.starts_with("COM") || upper.starts_with("LPT")) &&
           upper[3] >= '1' && upper[3] <= '9');
      if (name.empty() || name == "." || name == ".." || reserved || name.back() == '.' ||
          name.back() == ' ' || name.find_first_of("\\/:*?\"<>|") != std::string::npos) {
        result.error = "This disc has files that can't be copied to this PC.";
        cleanup();
        return result;
      }
      item.relative /= rex::to_path(name);
      const auto output = staging / item.relative;
      if (item.entry->attributes() & filesystem::kFileAttributeDirectory) {
        std::filesystem::create_directory(output);
        for (const auto& child : item.entry->children())
          pending.push_back({child.get(), item.relative});
        continue;
      }
      filesystem::File* file = nullptr;
      if (XFAILED(const_cast<filesystem::Entry*>(item.entry)
                      ->Open(filesystem::FileAccess::kGenericRead, &file)))
        throw std::runtime_error(
            "Unable to read the game. Check that the disc or drive is connected, and try again.");
      struct Close {
        filesystem::File* file;
        ~Close() { file->Destroy(); }
      } close{file};
      std::ofstream output_file(output, std::ios::binary);
      if (!output_file)
        throw std::runtime_error(
            "Unable to copy the game files. Check that there's enough free space, and try again.");
      for (size_t offset = 0; offset < item.entry->size();) {
        if (cancelled && cancelled()) {
          result.cancelled = true;
          output_file.close();
          cleanup();
          return result;
        }
        const size_t count = std::min(buffer.size(), item.entry->size() - offset);
        size_t read = 0;
        if (XFAILED(file->ReadSync(std::span(buffer).first(count), offset, &read)) || read != count)
          throw std::runtime_error(
              "Unable to read the game. Check that the disc or drive is connected, and try again.");
        output_file.write(reinterpret_cast<const char*>(buffer.data()), count);
        if (!output_file)
          throw std::runtime_error(
              "Unable to copy the game files. Check that there's enough free space, and try "
              "again.");
        offset += count;
        copied += count;
        if (progress)
          progress(copied, total);
      }
      if (!output_file.flush())
        throw std::runtime_error(
            "Unable to copy the game files. Check that there's enough free space, and try again.");
    }
    if (cancelled && cancelled()) {
      result.cancelled = true;
      cleanup();
      return result;
    }
    std::filesystem::rename(staging, target);
    owns_staging = false;
    result.folder = target;
  } catch (const std::exception& error) {
    REXLOG_WARN("Copying the game from {} failed: {}", path_to_utf8(image), error.what());
    result.error = error.what();
    cleanup();
  }
  return result;
}
}
