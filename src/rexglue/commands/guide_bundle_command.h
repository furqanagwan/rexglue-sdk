/**
 * @file        rexglue/commands/guide_bundle_command.h
 * @brief       rexglue guide-bundle: the Xbox guide's console files for embedding (RG-GDK-041)
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

void RegisterGuideBundle(CLI::App& parent, const CliContext& ctx, DeferredAction& pending);

}
