/**
 * @file        rex/codegen/code_patches.h
 * @brief       Guest code patches applied to the image before analysis
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <string>
#include <vector>

#include <rex/codegen/config.h>
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
Result<std::vector<std::string>> ApplyCodePatches(BinaryView& binary,
                                                  const std::vector<CodePatch>& patches);

}  // namespace rex::codegen
