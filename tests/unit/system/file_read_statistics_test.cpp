// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <rex/system/file_read_statistics.h>

using rex::system::FileReadStatistics;
using namespace std::chrono_literals;

TEST_CASE("File reads are bucketed by size", "[system][file_read_statistics]") {
  CHECK(FileReadStatistics::SizeBucket(0) == 0);
  CHECK(FileReadStatistics::SizeBucket(4096) == 0);
  CHECK(FileReadStatistics::SizeBucket(4097) == 1);
  CHECK(FileReadStatistics::SizeBucket(65536) == 1);
  CHECK(FileReadStatistics::SizeBucket(65537) == 2);
  CHECK(FileReadStatistics::SizeBucket(1024 * 1024) == 2);
  CHECK(FileReadStatistics::SizeBucket(1024 * 1024 + 1) == 3);
}

TEST_CASE("File read summary totals and resets", "[system][file_read_statistics]") {
  FileReadStatistics statistics;
  statistics.Record(2048, 1ms);
  statistics.Record(2 * 1024 * 1024, 5ms);
  statistics.Record(100000, 2ms);

  const auto summary = statistics.TakeSummary();
  CHECK(summary.reads == 3);
  CHECK(summary.bytes == 2048 + 2 * 1024 * 1024 + 100000);
  CHECK(summary.blocked == 8ms);
  CHECK(summary.longest == 5ms);
  CHECK(summary.reads_by_size == std::array<uint64_t, 4>{1, 0, 1, 1});

  const auto empty = statistics.TakeSummary();
  CHECK(empty.reads == 0);
  CHECK(empty.blocked == 0ms);
}

TEST_CASE("File read summary text reports blocked share", "[system][file_read_statistics]") {
  rex::system::FileReadSummary summary;
  summary.reads = 4;
  summary.bytes = 1024 * 1024;
  summary.blocked = 250ms;
  summary.longest = 100ms;
  const std::string text = FileReadStatistics::Describe(summary, 5s);
  CHECK(text.find("4 reads") != std::string::npos);
  CHECK(text.find("1.0 MiB") != std::string::npos);
  CHECK(text.find("blocked 250.0 ms (5.0% of the interval") != std::string::npos);
}
