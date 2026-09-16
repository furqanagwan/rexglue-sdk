/**
 * @file        rexglue/commands/resources_command.h
 * @brief       List or extract the resources embedded in a XEX
 *
 * @license     BSD 3-Clause License
 */

#pragma once

#include "../cli_utils.h"

namespace CLI {
class App;
}

namespace rexglue::cli {

void RegisterResources(CLI::App& parent, const CliContext& ctx, DeferredAction& pending);

}  // namespace rexglue::cli
