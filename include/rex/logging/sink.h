/**
 * @file        rex/logging/sink.h
 * @brief       Thread-safe ring-buffer spdlog sink for in-memory log capture
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <rex/logging/types.h>

#include <spdlog/sinks/base_sink.h>

#include <array>
#include <cstddef>
#include <mutex>
#include <string>
#include <vector>

namespace rex {

struct LogEntry {
  spdlog::level::level_enum level = spdlog::level::info;
  std::string category;
  std::string text;
};

class LogCaptureSink : public spdlog::sinks::base_sink<std::mutex> {
 public:
  static constexpr size_t kCapacity = 2048;

  void CopyEntries(std::vector<LogEntry>& out) const {
    std::lock_guard lock(mutable_mutex_);
    out.clear();
    out.reserve(count_);
    if (count_ < kCapacity) {
      for (size_t i = 0; i < count_; ++i) {
        out.push_back(buf_[i]);
      }
    } else {
      for (size_t i = 0; i < kCapacity; ++i) {
        out.push_back(buf_[(write_pos_ + i) % kCapacity]);
      }
    }
  }

  uint64_t generation() const {
    std::lock_guard lock(mutable_mutex_);
    return generation_;
  }

 protected:
  void sink_it_(const spdlog::details::log_msg& msg) override {
    std::string cat(msg.logger_name.begin(), msg.logger_name.end());

    spdlog::memory_buf_t formatted;
    formatter_->format(msg, formatted);

    std::string text(formatted.begin(), formatted.end());
    while (!text.empty() && (text.back() == '\n' || text.back() == '\r')) {
      text.pop_back();
    }

    std::lock_guard lock(mutable_mutex_);
    buf_[write_pos_] = LogEntry{msg.level, std::move(cat), std::move(text)};
    write_pos_ = (write_pos_ + 1) % kCapacity;
    if (count_ < kCapacity)
      ++count_;
    ++generation_;
  }

  void flush_() override {}

 private:
  std::array<LogEntry, kCapacity> buf_{};
  size_t write_pos_ = 0;
  size_t count_ = 0;
  uint64_t generation_ = 0;
  mutable std::mutex mutable_mutex_;
};

}
