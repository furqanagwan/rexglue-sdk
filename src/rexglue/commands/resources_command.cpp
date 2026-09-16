/**
 * @file        rexglue/commands/resources_command.cpp
 * @brief       List or extract the resources embedded in a XEX
 *
 * @license     BSD 3-Clause License
 */

#include "resources_command.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <rex/kernel/init.h>
#include <rex/logging.h>
#include <rex/memory.h>
#include <rex/result.h>
#include <rex/runtime.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xtypes.h>
#include <rex/system/user_module.h>
#include <rex/system/util/xex2_info.h>

namespace rexglue::cli {

namespace {

// X_STATUS_SUCCESS casts to the runtime's status type.
using X_STATUS = rex::X_STATUS;

struct ResourcesArgs {
  std::string xex;
  std::string output_dir;
};

// What a blob looks like, so a listing says something useful about it.
std::string_view DescribeBlob(const uint8_t* data, size_t size) {
  if (size >= 4) {
    if (std::memcmp(data, "XUIZ", 4) == 0) {
      return "XUI package";
    }
    if (std::memcmp(data, "XUIB", 4) == 0) {
      return "XUI scene";
    }
    if (std::memcmp(data, "XUIS", 4) == 0) {
      return "XUI strings";
    }
    if (std::memcmp(data, "XDBF", 4) == 0) {
      return "title database";
    }
    if (std::memcmp(data, "\x89PNG", 4) == 0) {
      return "PNG";
    }
    if (std::memcmp(data, "RIFF", 4) == 0) {
      return "RIFF";
    }
  }
  return "data";
}

// A resource's eight-character name, trimmed of its padding and of anything
// that has no business in a file name.
std::string SafeName(const char (&name)[8]) {
  std::string result(name, 8);
  result.erase(std::find(result.begin(), result.end(), '\0'), result.end());
  while (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  for (char& character : result) {
    if (character == '/' || character == '\\' || character == ':' || character < 0x20) {
      character = '_';
    }
  }
  return result.empty() ? std::string("resource") : result;
}

rex::Result<void> Resources(const ResourcesArgs& args, const CliContext& ctx) {
  namespace fs = std::filesystem;
  const fs::path xex_path = fs::absolute(args.xex);
  const fs::path game_root = xex_path.parent_path();

  // The runtime does the decrypting and decompressing; this only reads what it
  // maps in. That means a dashboard XEX the user owns gives up its own guide
  // artwork the same way a game gives up its achievement icons.
  auto runtime = std::make_unique<rex::Runtime>(game_root.string());
  auto status = runtime->Setup(rex::RuntimeConfig{
      .kernel_init = rex::kernel::InitializeKernel,
      .tool_mode = true,
  });
  if (status != X_STATUS_SUCCESS) {
    return rex::Err(rex::ErrorCategory::IO,
                    fmt::format("Failed to initialize the runtime: {:#x}", status));
  }

  const std::string vfs_path = "game:\\" + xex_path.filename().string();
  status = runtime->LoadXexImage(vfs_path);
  if (status != X_STATUS_SUCCESS) {
    return rex::Err(rex::ErrorCategory::Format,
                    fmt::format("Failed to load {}: {:#x}", xex_path.string(), status));
  }

  auto module = runtime->kernel_state()->GetExecutableModule();
  if (!module) {
    return rex::Err(rex::ErrorCategory::Format, "The XEX loaded without an executable module");
  }

  rex::xex2_opt_resource_info* header = nullptr;
  if (module->GetOptHeader(rex::XEX_HEADER_RESOURCE_INFO, reinterpret_cast<void**>(&header)) !=
          X_STATUS_SUCCESS ||
      !header) {
    return rex::Err(rex::ErrorCategory::NotFound, "The XEX carries no resources");
  }

  const uint32_t count = (header->size - 4) / uint32_t(sizeof(rex::xex2_resource));
  REXLOG_INFO("{}: {} resources", xex_path.filename().string(), count);

  std::error_code error;
  const bool extracting = !args.output_dir.empty();
  const fs::path output(args.output_dir);
  if (extracting) {
    if (!ctx.overwrite_existing && fs::exists(output, error) && !fs::is_empty(output, error)) {
      return rex::Err(rex::ErrorCategory::Validation,
                      fmt::format("{} is not empty; pass --force to write into it anyway",
                                  output.string()));
    }
    fs::create_directories(output, error);
  }

  for (uint32_t i = 0; i < count; ++i) {
    const auto& resource = header->resources[i];
    const uint8_t* data = runtime->memory()->TranslateVirtual(resource.address);
    const std::string name = SafeName(resource.name);
    if (!data || resource.size == 0) {
      REXLOG_WARN("  {} is empty or outside the image", name);
      continue;
    }
    REXLOG_INFO("  {:<10} {:>10} bytes  {}", name, uint32_t(resource.size),
                DescribeBlob(data, resource.size));
    if (!extracting) {
      continue;
    }
    const fs::path target = output / name;
    std::ofstream file(target, std::ios::binary);
    if (!file ||
        !file.write(reinterpret_cast<const char*>(data), std::streamsize(resource.size))) {
      return rex::Err(rex::ErrorCategory::IO, fmt::format("Failed to write {}", target.string()));
    }
  }

  if (extracting) {
    REXLOG_INFO("Wrote {} resources to {}", count, output.string());
  }
  return rex::Ok();
}

}  // namespace

void RegisterResources(CLI::App& parent, const CliContext& ctx, DeferredAction& pending) {
  auto* resources =
      parent
          .add_subcommand("resources",
                          "List or extract the resources embedded in a XEX, such as the UI "
                          "packages in a dashboard the user owns")
          ->fallthrough();
  auto args = std::make_shared<ResourcesArgs>();
  resources->add_option("xex", args->xex, "XEX to read")
      ->type_name("XEX")
      ->required()
      ->check(CLI::ExistingFile);
  resources->add_option("-o,--output", args->output_dir,
                        "Folder to write the resources into; without it they are only listed")
      ->type_name("DIR");
  resources->callback([args, &ctx, &pending]() {
    pending = [args, &ctx]() { return Resources(*args, ctx); };
  });
}

}  // namespace rexglue::cli
