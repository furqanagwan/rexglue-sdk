/**
 * @file        rex/filesystem/disc_image_extractor.h
 * @brief       Extracts every file from an Xbox 360 disc image to a host folder
 *
 * @license     BSD 3-Clause License
 */

#pragma once

#include <atomic>
#include <cstdint>
#include <filesystem>
#include <string>

namespace rex::filesystem {

// Copies the contents of an Xbox 360 disc image (XISO/GoD-style .iso) into a
// host folder, preserving the folder structure. Used by the `rexglue extract`
// command and by apps that install a game from the player's own disc image.
class DiscImageExtractor {
 public:
  // Updated from the extracting thread; safe to read from another thread.
  struct Progress {
    std::atomic<uint64_t> copied_bytes{0};
    std::atomic<uint64_t> total_bytes{0};
  };

  // Returns false and sets error() when the image cannot be read, a file name
  // is unsafe, or a file cannot be written.
  bool Extract(const std::filesystem::path& disc_image, const std::filesystem::path& destination,
               Progress& progress);

  const std::string& error() const { return error_; }

 private:
  std::string error_;
};

}  // namespace rex::filesystem
