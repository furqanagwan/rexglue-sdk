// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/system/file_read_statistics.h>

#include <algorithm>

#include <fmt/format.h>
#include <rex/cvar.h>
#include <rex/logging.h>

REXCVAR_DEFINE_INT32(file_read_stats_interval, 0, "Kernel",
                     "Log guest file reads (count, bytes, time blocked, sizes) every this many "
                     "seconds; 0 = off")
    .range(0, 3600);

namespace rex::system {
namespace {

using Clock = std::chrono::steady_clock;

std::atomic<int64_t> next_report_ticks{0};
std::atomic<int64_t> interval_start_ticks{0};

void ReportWhenIntervalEnds(FileReadStatistics& statistics) {
  const int32_t interval_seconds = REXCVAR_GET(file_read_stats_interval);
  if (interval_seconds <= 0) {
    return;
  }
  const int64_t now = Clock::now().time_since_epoch().count();
  const int64_t interval =
      std::chrono::duration_cast<Clock::duration>(std::chrono::seconds(interval_seconds)).count();
  int64_t due = next_report_ticks.load(std::memory_order_relaxed);
  if (due == 0) {
    next_report_ticks.compare_exchange_strong(due, now + interval);
    interval_start_ticks.store(now, std::memory_order_relaxed);
    return;
  }
  if (now < due || !next_report_ticks.compare_exchange_strong(due, now + interval)) {
    return;
  }
  const int64_t started = interval_start_ticks.exchange(now, std::memory_order_relaxed);
  const auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::duration(now - started));
  REXSYS_INFO("{}", FileReadStatistics::Describe(statistics.TakeSummary(), elapsed));
}

}

FileReadStatistics& FileReadStatistics::Global() {
  static FileReadStatistics statistics;
  return statistics;
}

size_t FileReadStatistics::SizeBucket(uint64_t bytes) {
  return size_t(std::ranges::lower_bound(kSizeBucketLimits, bytes) - kSizeBucketLimits.begin());
}

void FileReadStatistics::Record(uint64_t bytes, std::chrono::nanoseconds blocked) {
  reads_.fetch_add(1, std::memory_order_relaxed);
  bytes_.fetch_add(bytes, std::memory_order_relaxed);
  blocked_nanoseconds_.fetch_add(blocked.count(), std::memory_order_relaxed);
  int64_t longest = longest_nanoseconds_.load(std::memory_order_relaxed);
  while (blocked.count() > longest && !longest_nanoseconds_.compare_exchange_weak(
                                          longest, blocked.count(), std::memory_order_relaxed)) {}
  reads_by_size_[SizeBucket(bytes)].fetch_add(1, std::memory_order_relaxed);
}

FileReadSummary FileReadStatistics::TakeSummary() {
  FileReadSummary summary;
  summary.reads = reads_.exchange(0, std::memory_order_relaxed);
  summary.bytes = bytes_.exchange(0, std::memory_order_relaxed);
  summary.blocked =
      std::chrono::nanoseconds(blocked_nanoseconds_.exchange(0, std::memory_order_relaxed));
  summary.longest =
      std::chrono::nanoseconds(longest_nanoseconds_.exchange(0, std::memory_order_relaxed));
  for (size_t i = 0; i < reads_by_size_.size(); ++i) {
    summary.reads_by_size[i] = reads_by_size_[i].exchange(0, std::memory_order_relaxed);
  }
  return summary;
}

std::string FileReadStatistics::Describe(const FileReadSummary& summary,
                                         std::chrono::nanoseconds elapsed) {
  using Milliseconds = std::chrono::duration<double, std::milli>;
  const double elapsed_ms = Milliseconds(elapsed).count();
  const double blocked_ms = Milliseconds(summary.blocked).count();
  return fmt::format(
      "File reads: {} reads, {:.1f} MiB in {:.1f} s; blocked {:.1f} ms ({:.1f}% of the interval, "
      "summed over threads), longest {:.2f} ms; sizes <=4K {}, <=64K {}, <=1M {}, >1M {}",
      summary.reads, double(summary.bytes) / (1024.0 * 1024.0), elapsed_ms / 1000.0, blocked_ms,
      elapsed_ms > 0 ? 100.0 * blocked_ms / elapsed_ms : 0.0, Milliseconds(summary.longest).count(),
      summary.reads_by_size[0], summary.reads_by_size[1], summary.reads_by_size[2],
      summary.reads_by_size[3]);
}

ScopedFileReadTimer::ScopedFileReadTimer(const uint32_t* bytes_read)
    : bytes_read_(bytes_read),
      start_(Clock::now()),
      enabled_(REXCVAR_GET(file_read_stats_interval) > 0) {}

ScopedFileReadTimer::~ScopedFileReadTimer() {
  if (!enabled_) {
    return;
  }
  auto& statistics = FileReadStatistics::Global();
  statistics.Record(bytes_read_ ? *bytes_read_ : 0,
                    std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start_));
  ReportWhenIntervalEnds(statistics);
}

}
