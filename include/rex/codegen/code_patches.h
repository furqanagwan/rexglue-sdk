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

/**
 * Writes every enabled `[[patch]]` into the image, before instructions are
 * decoded, so the generated C++ is built from the patched code.
 *
 * Only executable sections can be patched: the runtime loads the original
 * image into guest memory, so a data patch would never reach the running
 * title. A disabled patch is skipped. Nothing is written, and an error names
 * the patch, when an enabled patch is malformed, reaches outside the code
 * sections, or overlaps another enabled patch.
 *
 * @return The names of the applied patches, in definition order.
 */
/// Writes the enabled, non-switchable patches into codegen's copy of the
/// image. Returns their names.
Result<std::vector<std::string>> ApplyCodePatches(BinaryView& binary,
                                                  const std::vector<CodePatch>& patches);

/// A switchable patch as the title's patch table lists it.
struct SwitchablePatch {
  std::string name;
  bool enabled = false;  ///< Its state when the title starts
  std::string category = "patch";
};

struct SwitchablePatches {
  std::vector<SwitchablePatch> patches;
  std::map<uint32_t, SwitchedWord> words;     ///< By guest address
  std::multimap<uint32_t, SwitchedSet> sets;  ///< By the guest address they run before
};

/// Checks the switchable patches and works out, per instruction word, the
/// original and patched versions. They are not written into the image, so
/// analysis sees the original code. Every write must stay in code, and
/// neither version of a word may be a branch, call, trap or system call:
/// switching one of those would change the control flow analysis found.
/// A patch's register sets must be at word addresses in code, and one keyed
/// on lr needs the link register kept (not skip_lr).
Result<SwitchablePatches> PrepareSwitchablePatches(const BinaryView& binary,
                                                   const std::vector<CodePatch>& patches,
                                                   bool keeps_lr = true);

}  // namespace rex::codegen
