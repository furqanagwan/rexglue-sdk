/**
 * @file        rexglue/commands/extract_command.h
 * @brief       Extract an Xbox 360 disc image into a project's assets folder
 *
 * @license     BSD 3-Clause License
 */

#pragma once

#include "../cli_utils.h"

namespace CLI {
class App;
}

namespace rexglue::cli {

void RegisterExtract(CLI::App& parent, const CliContext& ctx, DeferredAction& pending);

}  // namespace rexglue::cli
