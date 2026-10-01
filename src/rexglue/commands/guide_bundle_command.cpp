/**
 * @file        rexglue/commands/guide_bundle_command.cpp
 * @brief       rexglue guide-bundle: the Xbox guide's console files for embedding (RG-GDK-041)
 *
 * Reads the system modules the Xbox guide needs (hud, huduiskin, xam,
 * gamerprofile) from the builder's own console system update and writes them
 * as one bundle. rexglue_configure_target runs this at build time and embeds
 * the bundle into the title, so players need nothing for the guide.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "guide_bundle_command.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <rex/logging.h>
#include <rex/ui/xui/system_update.h>

namespace rexglue::cli {

using rex::Err;
using rex::ErrorCategory;
using rex::Result;

namespace {

struct GuideBundleArgs {
  std::string system_update;
  std::string output;
};

Result<void> WriteGuideBundle(const GuideBundleArgs& args) {
  using rex::ui::xui::SystemUpdate;
  std::string error;
  auto modules = SystemUpdate::ReadModules(args.system_update, &error);
  // Check the guide can be built from it before anything is embedded.
  if (!modules || !SystemUpdate::FromModules(*modules, &error)) {
    return Err<void>(ErrorCategory::Config, fmt::format("{}: {}", args.system_update, error));
  }
  const auto bundle = SystemUpdate::WriteBundle(*modules);
  const std::filesystem::path out(args.output);
  std::error_code ec;
  if (out.has_parent_path()) {
    std::filesystem::create_directories(out.parent_path(), ec);
  }
  // Written beside, then moved, so a failed write never leaves half a bundle.
  const std::filesystem::path temp = out.string() + ".tmp";
  {
    std::ofstream file(temp, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(bundle.data()), std::streamsize(bundle.size()));
    if (!file) {
      return Err<void>(ErrorCategory::IO, fmt::format("could not write {}", temp.string()));
    }
  }
  std::filesystem::rename(temp, out, ec);
  if (ec) {
    return Err<void>(ErrorCategory::IO,
                     fmt::format("could not write {}: {}", out.string(), ec.message()));
  }
  REXLOG_INFO("Xbox guide bundle: {} modules, {} KiB -> {}", modules->size(), bundle.size() / 1024,
              out.string());
  return rex::Ok();
}

}  // namespace

void RegisterGuideBundle(CLI::App& parent, const CliContext& ctx, DeferredAction& pending) {
  (void)ctx;
  auto args = std::make_shared<GuideBundleArgs>();
  auto* sub = parent.add_subcommand(
      "guide-bundle", "Bundle the Xbox guide's console files for embedding in a title");
  sub->add_option("system_update", args->system_update,
                  "$SystemUpdate folder (dashboard 2.0.17559), its su*_00000000 package, or a "
                  "folder of $flash_<module>.xex files")
      ->required()
      ->type_name("PATH");
  sub->add_option("-o,--output", args->output, "Bundle file to write")
      ->required()
      ->type_name("PATH");
  sub->callback([args, &pending]() {
    pending = [args]() -> Result<void> { return WriteGuideBundle(*args); };
  });
}

}  // namespace rexglue::cli
