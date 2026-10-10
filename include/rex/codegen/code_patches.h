/**
 * @file        rex/codegen/code_patches.h
 * @brief       Guest code patches applied to the image before analysis
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <map>
#include <string>
#include <vector>

#include <rex/codegen/config.h>
#include <rex/codegen/function_types.h>
#include <rex/result.h>

namespace rex::codegen {

class BinaryView;

Result<std::vector<std::string>> ApplyCodePatches(BinaryView& binary,
                                                  const std::vector<CodePatch>& patches);

struct SwitchablePatch {
  std::string name;
  bool enabled = false;
  std::string category = "patch";
};

struct SwitchablePatches {
  std::vector<SwitchablePatch> patches;
  std::map<uint32_t, SwitchedWord> words;
  std::multimap<uint32_t, SwitchedSet> sets;
};

Result<SwitchablePatches> PrepareSwitchablePatches(const BinaryView& binary,
                                                   const std::vector<CodePatch>& patches,
                                                   bool keeps_lr = true);

}
