/**
 * @file        rex/codegen/project_recompiler.h
 * @brief       Project-level recompiler driving manifest-based multi-binary codegen
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <string>
#include <vector>

#include <rex/codegen/manifest.h>
#include <rex/codegen/progress_reporter.h>
#include <rex/result.h>

namespace rex::codegen {

struct ProjectRecompilerOptions {
  std::vector<std::string> targets;
  bool force = false;
  bool enableExceptionHandlers = false;
  ProgressReporter* reporter = nullptr;

  bool ignoreStamp = false;

  std::string sdkVersion;
};

class ProjectRecompiler {
 public:
  explicit ProjectRecompiler(ManifestConfig manifest);
  Result<void> Run(const ProjectRecompilerOptions& opts);

  const std::vector<std::string>& deletedFiles() const { return deletedFiles_; }

  const std::vector<std::string>& writtenFiles() const { return writtenFiles_; }

  const std::vector<std::string>& unchangedFiles() const { return unchangedFiles_; }

  const std::vector<std::string>& skippedModules() const { return skippedModules_; }

 private:
  struct Pass {
    BinaryConfig entrypoint;
    std::vector<BinaryConfig> modules;
    std::filesystem::path updatePackage;
    uint32_t titleUpdateVersion = 0;
  };
  Result<void> RunPass(const ProjectRecompilerOptions& opts, Pass pass,
                       std::vector<std::filesystem::path>& allInputs,
                       std::vector<std::string>& fingerprints);

  ManifestConfig manifest_;
  std::vector<std::string> deletedFiles_;
  std::vector<std::string> writtenFiles_;
  std::vector<std::string> unchangedFiles_;
  std::vector<std::string> skippedModules_;
};

}
