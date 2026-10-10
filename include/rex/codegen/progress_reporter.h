/**
 * @file        rex/codegen/progress_reporter.h
 * @brief       Abstract callback interface for codegen pipeline progress
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace rex::codegen {

struct BinaryInfo {
  std::string_view name;
  uint32_t title_id = 0;
  uint32_t media_id = 0;
  uint32_t version_major = 0;
  uint32_t version_minor = 0;
  uint32_t version_build = 0;
  uint32_t version_qfe = 0;
  uint32_t pe_time_date_stamp = 0;
};

class ProgressReporter {
 public:
  virtual ~ProgressReporter() = default;

  virtual void binaryInfo(const BinaryInfo&) {}

  virtual void moduleStarted(std::string_view name, std::size_t index, std::size_t total) = 0;

  virtual void phaseChanged(std::string_view name) = 0;

  virtual void moduleFinished(std::chrono::milliseconds elapsed) = 0;

  virtual void projectPhaseStarted(std::string_view name) = 0;

  virtual void projectPhaseFinished() = 0;
};

}
