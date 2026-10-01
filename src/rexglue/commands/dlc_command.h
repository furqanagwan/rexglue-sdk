/**
 * @file        rexglue/commands/dlc_command.h
 * @brief       rexglue dlc-catalog and dlc-find: a title's add-ons from the 360 marketplace
 *              catalogue (RG-GDK-050)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include "../cli_utils.h"

namespace CLI {
class App;
}

namespace rexglue::cli {

void RegisterDlcCommands(CLI::App& parent, const CliContext& ctx, DeferredAction& pending);

}  // namespace rexglue::cli
