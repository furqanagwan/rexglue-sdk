// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <string>

namespace rex::system {

struct FileReadSummary {
  uint64_t reads = 0;
  uint64_t bytes = 0;
  std::chrono::nanoseconds blocked{};
  std::chrono::nanoseconds longest{};
  std::array<uint64_t, 4> reads_by_size{};
};

class FileReadStatistics {
 public:
  static constexpr std::array<uint64_t, 3> kSizeBucketLimits = {4 * 1024, 64 * 1024, 1024 * 1024};

  static FileReadStatistics& Global();

  void Record(uint64_t bytes, std::chrono::nanoseconds blocked);
  FileReadSummary TakeSummary();

  static size_t SizeBucket(uint64_t bytes);
  static std::string Describe(const FileReadSummary& summary, std::chrono::nanoseconds elapsed);

 private:
  std::atomic<uint64_t> reads_{0};
  std::atomic<uint64_t> bytes_{0};
  std::atomic<int64_t> blocked_nanoseconds_{0};
  std::atomic<int64_t> longest_nanoseconds_{0};
  std::array<std::atomic<uint64_t>, 4> reads_by_size_{};
};

class ScopedFileReadTimer {
 public:
  explicit ScopedFileReadTimer(const uint32_t* bytes_read);
  ~ScopedFileReadTimer();
  ScopedFileReadTimer(const ScopedFileReadTimer&) = delete;
  ScopedFileReadTimer& operator=(const ScopedFileReadTimer&) = delete;

 private:
  const uint32_t* bytes_read_;
  std::chrono::steady_clock::time_point start_;
  bool enabled_;
};

}  // namespace rex::system
