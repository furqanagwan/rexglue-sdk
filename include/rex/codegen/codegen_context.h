/**
 * @file        rexcodegen/codegen_context.h
 * @brief       Unified context for codegen pipeline
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
#include <unordered_map>
#include <vector>

#include <rex/codegen/analysis_errors.h>
#include <rex/codegen/binary_view.h>
#include <rex/codegen/code_patches.h>
#include <rex/codegen/code_region.h>
#include <rex/codegen/config.h>
#include <rex/codegen/function_graph.h>
#include <rex/result.h>

namespace rex {
class Runtime;

namespace runtime {
class ExportResolver;
}
}

namespace rex::codegen {

class DecodedBinary;
struct SectionInfo;
struct FunctionEntry;
struct FunctionConfig;

struct AnalysisState {
  std::string format;
  uint64_t loadAddress = 0;
  uint64_t entryPoint = 0;
  uint64_t imageSize = 0;

  std::vector<SectionInfo> sections;
  std::vector<FunctionEntry> analyzedFunctions;
  std::unordered_map<uint32_t, std::vector<uint32_t>> chunksByParent;

  uint32_t restGpr14Address = 0;
  uint32_t saveGpr14Address = 0;
  uint32_t restFpr14Address = 0;
  uint32_t saveFpr14Address = 0;
  uint32_t restVmx14Address = 0;
  uint32_t saveVmx14Address = 0;
  uint32_t restVmx64Address = 0;
  uint32_t saveVmx64Address = 0;

  std::unordered_map<uint32_t, uint32_t> invalidInstructions;
  std::unordered_set<uint32_t> knownIndirectCalls;
  std::vector<uint32_t> exceptionHandlerFuncs;
  std::vector<uint32_t> ehDiscoveredFuncs;
};

class CodegenContext {
 public:
  static Result<CodegenContext> Create(const std::filesystem::path& configPath, Runtime& runtime);

  static CodegenContext Create(BinaryView binary, RecompilerConfig config);

  CodegenContext(const CodegenContext&) = delete;
  CodegenContext& operator=(const CodegenContext&) = delete;
  CodegenContext(CodegenContext&&);
  CodegenContext& operator=(CodegenContext&&);
  ~CodegenContext();

  FunctionGraph graph;
  AnalysisErrors errors;

  struct {
    std::vector<CodeRegion> codeRegions;
    std::vector<std::pair<uint32_t, uint32_t>> dataRegions;
    std::unordered_map<uint32_t, uint32_t> pdataSizes;
  } scan;

  const BinaryView& binary() const { return binary_; }
  BinaryView& binary() { return binary_; }

  DecodedBinary& decoded();
  const DecodedBinary& decoded() const;

  void initDecoded();

  bool hasDecoded() const { return decoded_ != nullptr; }

  RecompilerConfig& Config() { return config_; }
  const RecompilerConfig& Config() const { return config_; }

  AnalysisState& analysisState() { return analysisState_; }
  const AnalysisState& analysisState() const { return analysisState_; }

  runtime::ExportResolver* resolver() const { return resolver_; }
  void setResolver(runtime::ExportResolver* r) { resolver_ = r; }

  const std::filesystem::path& configDir() const { return configDir_; }
  void setConfigDir(const std::filesystem::path& dir) { configDir_ = dir; }
  const std::string& sourceGuestPath() const { return source_guest_path_; }
  void setSourceGuestPath(std::string path) { source_guest_path_ = std::move(path); }

  void setDllModule(bool is_dll) { is_dll_module_ = is_dll; }
  bool isDllModule() const { return is_dll_module_; }

  void setHasDllModules(bool has) { has_dll_modules_ = has; }
  bool hasDllModules() const { return has_dll_modules_; }

  void setFunctionTableBase(uint32_t base) { function_table_base_ = base; }
  uint32_t functionTableBase() const { return function_table_base_; }

  const std::vector<std::string>& appliedPatches() const { return applied_patches_; }
  void setAppliedPatches(std::vector<std::string> names) { applied_patches_ = std::move(names); }

  const SwitchablePatches& switchablePatches() const { return switchable_patches_; }
  void setSwitchablePatches(SwitchablePatches patches) { switchable_patches_ = std::move(patches); }

 private:
  CodegenContext() = default;

  BinaryView binary_;
  RecompilerConfig config_;
  AnalysisState analysisState_;
  std::unique_ptr<DecodedBinary> decoded_;
  runtime::ExportResolver* resolver_ = nullptr;
  std::filesystem::path configDir_;
  std::string source_guest_path_;
  bool is_dll_module_ = false;
  bool has_dll_modules_ = false;
  uint32_t function_table_base_ = 0;
  std::vector<std::string> applied_patches_;
  SwitchablePatches switchable_patches_;
};

}
