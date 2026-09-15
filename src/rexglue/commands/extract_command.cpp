/**
 * @file        rexglue/commands/extract_command.cpp
 * @brief       Extract an Xbox 360 disc image into a project's assets folder
 *
 * @license     BSD 3-Clause License
 */

#include "extract_command.h"

#include <filesystem>
#include <memory>
#include <string>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <rex/filesystem/disc_image_extractor.h>
#include <rex/logging.h>
#include <rex/result.h>

namespace rexglue::cli {

namespace {

struct ExtractArgs {
  std::string disc_image;
  std::string output_dir;
};

rex::Result<void> Extract(const ExtractArgs& args, const CliContext& ctx) {
  const std::filesystem::path output(args.output_dir);
  std::error_code error;
  if (!ctx.overwrite_existing && std::filesystem::exists(output, error) &&
      !std::filesystem::is_empty(output, error)) {
    return rex::Err(rex::ErrorCategory::Validation,
                    fmt::format("{} is not empty; pass --force to extract into it anyway",
                                output.string()));
  }

  rex::filesystem::DiscImageExtractor extractor;
  rex::filesystem::DiscImageExtractor::Progress progress;
  REXLOG_INFO("Extracting {} to {}", args.disc_image, output.string());
  if (!extractor.Extract(args.disc_image, output, progress)) {
    return rex::Err(rex::ErrorCategory::IO, extractor.error());
  }
  REXLOG_INFO("Extracted {:.2f} GB", double(progress.copied_bytes.load()) / (1024.0 * 1024 * 1024));
  return rex::Ok();
}

}  // namespace

void RegisterExtract(CLI::App& parent, const CliContext& ctx, DeferredAction& pending) {
  auto* extract =
      parent.add_subcommand("extract", "Extract an Xbox 360 disc image (.iso) to a folder")
          ->fallthrough();
  auto args = std::make_shared<ExtractArgs>();
  extract->add_option("disc_image", args->disc_image, "Xbox 360 disc image to read")
      ->type_name("ISO")
      ->required()
      ->check(CLI::ExistingFile);
  extract->add_option("output_dir", args->output_dir,
                      "Folder to extract into, e.g. the project's assets folder")
      ->type_name("DIR")
      ->required();
  extract->callback([args, &ctx, &pending]() {
    pending = [args, &ctx]() { return Extract(*args, ctx); };
  });
}

}  // namespace rexglue::cli
