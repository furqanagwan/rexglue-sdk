/**
 * @file        rex/codegen/codegen.h
 * @brief       Codegen pipeline orchestrator
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <filesystem>
#include <memory>

#include <rex/codegen/codegen_context.h>
#include <rex/result.h>

namespace rex {
class Runtime;
}

namespace rex::codegen {

class CodegenPipeline {
 public:
  ~CodegenPipeline();

  CodegenPipeline(const CodegenPipeline&) = delete;
  CodegenPipeline& operator=(const CodegenPipeline&) = delete;
  CodegenPipeline(CodegenPipeline&&) noexcept;
  CodegenPipeline& operator=(CodegenPipeline&&) noexcept;

  static Result<CodegenPipeline> Create(const std::filesystem::path& configPath);

  Result<void> Run(bool force = false);
  Result<void> RunAnalyze();
  Result<void> RunWrite(bool force = false);

  CodegenContext& context() { return *ctx_; }
  const CodegenContext& context() const { return *ctx_; }

 private:
  CodegenPipeline() = default;

  std::unique_ptr<Runtime> runtime_;
  std::unique_ptr<CodegenContext> ctx_;
};

}
