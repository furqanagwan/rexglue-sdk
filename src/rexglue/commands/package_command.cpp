#include "package_command.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <span>
#include <string>
#include <string_view>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <rex/filesystem/devices/stfs_container_device.h>
#include <rex/filesystem/entry.h>
#include <rex/filesystem/file.h>
#include <rex/hash.h>
#include <rex/logging.h>
#include <rex/result.h>

namespace rexglue::cli {
namespace {

struct PackageArgs {
  std::string package;
  std::string output_dir;
};

bool SafeName(std::string_view name) {
  return !name.empty() && name != "." && name != ".." &&
         name.find('/') == std::string_view::npos && name.find('\\') == std::string_view::npos;
}

rex::Result<void> ExtractEntry(rex::filesystem::Entry& entry,
                               const std::filesystem::path& destination) {
  if (!SafeName(entry.name())) {
    return rex::Err(rex::ErrorCategory::Validation, "Package contains an unsafe path component");
  }
  const auto target = destination / rex::to_path(entry.name());
  if (entry.attributes() & rex::filesystem::kFileAttributeDirectory) {
    std::error_code ec;
    std::filesystem::create_directories(target, ec);
    if (ec) return rex::Err(rex::ErrorCategory::IO, ec.message());
    for (const auto& child : entry.children()) {
      if (auto result = ExtractEntry(*child, target); !result) return result;
    }
    return rex::Ok();
  }

  std::error_code ec;
  std::filesystem::create_directories(target.parent_path(), ec);
  rex::filesystem::File* source = nullptr;
  if (XFAILED(entry.Open(rex::filesystem::FileAccess::kGenericRead, &source)) || !source) {
    return rex::Err(rex::ErrorCategory::IO, fmt::format("Unable to read {}", entry.path()));
  }
  std::ofstream output(target, std::ios::binary | std::ios::trunc);
  if (!output) {
    source->Destroy();
    return rex::Err(rex::ErrorCategory::IO, fmt::format("Unable to create {}", target.string()));
  }
  std::array<uint8_t, 256 * 1024> buffer{};
  size_t offset = 0;
  while (offset < entry.size()) {
    size_t read = 0;
    const size_t wanted = std::min(buffer.size(), entry.size() - offset);
    if (XFAILED(source->ReadSync(std::span<uint8_t>(buffer.data(), wanted), offset, &read)) ||
        read == 0) {
      source->Destroy();
      return rex::Err(rex::ErrorCategory::IO, fmt::format("Failed reading {}", entry.path()));
    }
    output.write(reinterpret_cast<const char*>(buffer.data()), std::streamsize(read));
    offset += read;
  }
  source->Destroy();
  output.close();
  if (!output) {
    return rex::Err(rex::ErrorCategory::IO, fmt::format("Failed writing {}", target.string()));
  }
  REXLOG_INFO("{} ({} bytes, xxh3 {})", target.string(), entry.size(), rex::hash_file(target));
  return rex::Ok();
}

rex::Result<void> InspectPackage(const PackageArgs& args, const CliContext& ctx) {
  const auto package_path = rex::to_path(args.package);
  const auto header = rex::filesystem::StfsContainerDevice::ReadPackageHeader(package_path);
  if (!header) return rex::Err(rex::ErrorCategory::Validation, "Not a supported STFS package");
  const auto& info = header->metadata.execution_info;
  REXLOG_INFO("Title ID {:08X}, media ID {:08X}, version {:08X}, content type {:08X}",
              uint32_t(info.title_id), uint32_t(info.media_id), uint32_t(info.version_value),
              static_cast<uint32_t>(header->metadata.content_type.get()));
  if (args.output_dir.empty()) return rex::Ok();

  const std::filesystem::path output = rex::to_path(args.output_dir);
  std::error_code ec;
  if (!ctx.overwrite_existing && std::filesystem::exists(output, ec) &&
      !std::filesystem::is_empty(output, ec)) {
    return rex::Err(rex::ErrorCategory::Validation,
                    fmt::format("{} is not empty; pass --force to overwrite", output.string()));
  }
  std::filesystem::create_directories(output, ec);
  rex::filesystem::StfsContainerDevice device("\\Package", package_path);
  if (!device.Initialize()) return rex::Err(rex::ErrorCategory::IO, "Unable to mount package");
  auto* root = device.ResolvePath("");
  if (!root) return rex::Err(rex::ErrorCategory::IO, "Package has no file tree");
  for (const auto& child : root->children()) {
    if (auto result = ExtractEntry(*child, output); !result) return result;
  }
  return rex::Ok();
}

}  // namespace

void RegisterPackage(CLI::App& parent, const CliContext& ctx, DeferredAction& pending) {
  auto args = std::make_shared<PackageArgs>();
  auto* command = parent.add_subcommand("package", "Inspect or extract an Xbox 360 STFS package")
                      ->fallthrough();
  command->add_option("package", args->package, "STFS package to read")
      ->required()
      ->check(CLI::ExistingFile);
  command->add_option("output_dir", args->output_dir, "Optional extraction folder");
  command->callback(
      [args, &ctx, &pending] { pending = [args, &ctx] { return InspectPackage(*args, ctx); }; });
}

}  // namespace rexglue::cli
