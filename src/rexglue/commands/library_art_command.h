/**
 * @file        rexglue/commands/library_art_command.h
 * @brief       rexglue library-art: a title's Xbox PC library tiles (RG-GDK-068)
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

void RegisterLibraryArt(CLI::App& parent, const CliContext& ctx, DeferredAction& pending);

}  // namespace rexglue::cli
