/**
 * @file        rex/codegen/codegen_writer.h
 * @brief       Consolidated codegen output writer
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <fmt/core.h>

#include <rex/codegen/codegen_context.h>

namespace rex {
class Runtime;
}

namespace rex::codegen {

bool IsGeneratedOutputName(std::string_view filename, std::string_view projectName);

class CodegenWriter {
 public:
  CodegenWriter(CodegenContext& ctx, Runtime* runtime = nullptr);

  bool write(bool force);

  const std::vector<std::string>& deletedFiles() const { return deletedFiles_; }

  const std::vector<std::string>& writtenFiles() const { return writtenFiles_; }

  const std::vector<std::string>& unchangedFiles() const { return unchangedFiles_; }

 private:
  CodegenContext& ctx_;
  Runtime* runtime_;

  std::string out;
  std::vector<std::pair<std::string, std::string>> pendingWrites;
  std::vector<std::string> deletedFiles_;
  std::vector<std::string> writtenFiles_;
  std::vector<std::string> unchangedFiles_;

  template <class... Args>
  void print(fmt::format_string<Args...> fmt, Args&&... args) {
    fmt::vformat_to(std::back_inserter(out), fmt.get(), fmt::make_format_args(args...));
  }

  template <class... Args>
  void println(fmt::format_string<Args...> fmt, Args&&... args) {
    fmt::vformat_to(std::back_inserter(out), fmt.get(), fmt::make_format_args(args...));
    out += '\n';
  }

  void SaveCurrentOutData(std::string_view name);
  bool FlushPendingWrites();

  FunctionGraph& graph();
  const FunctionGraph& graph() const;
  const BinaryView& binary() const;
  RecompilerConfig& config();
  const RecompilerConfig& config() const;
  AnalysisState& analysisState();
  const AnalysisState& analysisState() const;
};

}
