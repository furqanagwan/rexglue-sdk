/**
 * @file        filesystem/disc_image_extractor.cpp
 * @brief       Extracts every file from an Xbox 360 disc image to a host folder
 *
 * @license     BSD 3-Clause License
 */

#include <rex/filesystem/disc_image_extractor.h>

#include <algorithm>
#include <cstdio>
#include <memory>
#include <span>
#include <vector>

#include <rex/filesystem.h>
#include <rex/filesystem/devices/disc_image_device.h>
#include <rex/filesystem/entry.h>
#include <rex/filesystem/file.h>
#include <rex/system/xtypes.h>

namespace rex::filesystem {

namespace {

constexpr size_t kCopyChunkBytes = 4 * 1024 * 1024;

using GuestFile = std::unique_ptr<File, void (*)(File*)>;

bool IsSafePathComponent(const std::string& name) {
  return !name.empty() && name != "." && name != ".." &&
         name.find_first_of("/\\:") == std::string::npos;
}

class EntryCopier {
 public:
  EntryCopier(DiscImageExtractor::Progress& progress, std::string& error)
      : progress_(progress), error_(error), buffer_(kCopyChunkBytes) {}

  bool CopyChildren(Entry& folder, const std::filesystem::path& host_folder) {
    for (const auto& child : folder.children()) {
      if (!IsSafePathComponent(child->name())) {
        error_ = "Disc contains an unsafe file name: " + child->name();
        return false;
      }
      const auto host_path = host_folder / std::filesystem::u8path(child->name());
      const bool copied = (child->attributes() & kFileAttributeDirectory)
                              ? CopyFolder(*child, host_path)
                              : CopyFile(*child, host_path);
      if (!copied) {
        return false;
      }
    }
    return true;
  }

 private:
  bool CopyFolder(Entry& folder, const std::filesystem::path& host_path) {
    std::error_code error;
    std::filesystem::create_directories(host_path, error);
    if (error) {
      error_ = "Could not create " + host_path.string() + ": " + error.message();
      return false;
    }
    return CopyChildren(folder, host_path);
  }

  bool CopyFile(Entry& entry, const std::filesystem::path& host_path) {
    File* raw_file = nullptr;
    if (!XSUCCEEDED(entry.Open(FileAccess::kFileReadData, &raw_file)) || !raw_file) {
      error_ = "Could not read " + entry.path() + " from the disc image.";
      return false;
    }
    GuestFile guest_file(raw_file, [](File* file) { file->Destroy(); });

    std::FILE* host_file = OpenFile(host_path, "wb");
    if (!host_file) {
      error_ = "Could not create " + host_path.string() + ".";
      return false;
    }
    const bool copied = CopyContents(entry, *guest_file, host_file, host_path);
    std::fclose(host_file);
    return copied;
  }

  bool CopyContents(Entry& entry, File& guest_file, std::FILE* host_file,
                    const std::filesystem::path& host_path) {
    for (size_t offset = 0; offset < entry.size();) {
      const size_t wanted = std::min(buffer_.size(), entry.size() - offset);
      size_t read = 0;
      if (!XSUCCEEDED(guest_file.ReadSync(std::span<uint8_t>(buffer_.data(), wanted), offset,
                                          &read)) ||
          read == 0) {
        error_ = "Read error in " + entry.path() + "; the disc image may be damaged.";
        return false;
      }
      if (std::fwrite(buffer_.data(), 1, read, host_file) != read) {
        error_ = "Write error for " + host_path.string() + "; the disk may be full.";
        return false;
      }
      offset += read;
      progress_.copied_bytes += read;
    }
    return true;
  }

  DiscImageExtractor::Progress& progress_;
  std::string& error_;
  std::vector<uint8_t> buffer_;
};

}  // namespace

bool DiscImageExtractor::Extract(const std::filesystem::path& disc_image,
                                 const std::filesystem::path& destination, Progress& progress) {
  error_.clear();
  DiscImageDevice device("\\Device\\DiscImageExtractor", disc_image);
  if (!device.Initialize()) {
    error_ = "Not a readable Xbox 360 disc image: " + disc_image.string();
    return false;
  }
  progress.total_bytes = device.total_file_size();

  std::error_code folder_error;
  std::filesystem::create_directories(destination, folder_error);
  if (folder_error) {
    error_ = "Could not create " + destination.string() + ": " + folder_error.message();
    return false;
  }

  auto* root = device.ResolvePath("");
  if (!root) {
    error_ = "The disc image has no root folder.";
    return false;
  }
  EntryCopier copier(progress, error_);
  return copier.CopyChildren(*root, destination);
}

}  // namespace rex::filesystem
