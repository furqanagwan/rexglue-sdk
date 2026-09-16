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
#include <cstring>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <rex/kernel/init.h>
#include <rex/logging.h>
#include <rex/memory.h>
#include <rex/result.h>
#include <rex/runtime.h>
#include <rex/system/lzx.h>
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

struct Resource {
  std::string name;
  const uint8_t* data = nullptr;
  uint32_t size = 0;
};

uint32_t ReadBE32(const std::vector<uint8_t>& data, size_t offset) {
  return (uint32_t(data[offset]) << 24) | (uint32_t(data[offset + 1]) << 16) |
         (uint32_t(data[offset + 2]) << 8) | uint32_t(data[offset + 3]);
}

uint16_t ReadBE16(const std::vector<uint8_t>& data, size_t offset) {
  return uint16_t((uint16_t(data[offset]) << 8) | data[offset + 1]);
}

// A XEX's image, rebuilt from the file without the runtime.
//
// The runtime only accepts a module whose image holds a PE, which a
// resource-only module such as huduiskin.xex does not: it is a container for
// XUI packages, with no code, entry point or imports. Its image still unpacks
// the same way, so for reading resources the loader's rules can be set aside.
struct XexImage {
  uint32_t base = 0;
  std::vector<uint8_t> bytes;
  std::vector<Resource> resources;
};

rex::Result<XexImage> ReadImageDirect(const std::filesystem::path& path) {
  std::ifstream file(path, std::ios::binary);
  std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
  if (data.size() < 0x18 || std::memcmp(data.data(), "XEX2", 4) != 0) {
    return rex::Err<XexImage>(rex::ErrorCategory::Format, "Not a XEX2 file");
  }
  const uint32_t header_size = ReadBE32(data, 0x8);
  const uint32_t security_offset = ReadBE32(data, 0x10);
  const uint32_t header_count = ReadBE32(data, 0x14);
  if (header_size > data.size() || security_offset + 0x114 > data.size()) {
    return rex::Err<XexImage>(rex::ErrorCategory::Format, "The XEX headers are truncated");
  }

  uint32_t format_offset = 0;
  uint32_t resource_offset = 0;
  for (uint32_t i = 0; i < header_count; ++i) {
    const size_t entry = 0x18 + size_t(i) * 8;
    if (entry + 8 > header_size) {
      break;
    }
    const uint32_t key = ReadBE32(data, entry);
    const uint32_t value = ReadBE32(data, entry + 4);
    if (key == rex::XEX_HEADER_FILE_FORMAT_INFO) {
      format_offset = value;
    } else if (key == rex::XEX_HEADER_RESOURCE_INFO) {
      resource_offset = value;
    }
  }
  if (!format_offset || format_offset + 8 > header_size) {
    return rex::Err<XexImage>(rex::ErrorCategory::Format, "The XEX has no file format header");
  }
  if (!resource_offset || resource_offset + 4 > header_size) {
    return rex::Err<XexImage>(rex::ErrorCategory::NotFound, "The XEX carries no resources");
  }

  XexImage image;
  const uint32_t image_size = ReadBE32(data, security_offset + 0x4);
  image.base = ReadBE32(data, security_offset + 0x110);
  image.bytes.assign(image_size, 0);

  const uint32_t format_size = ReadBE32(data, format_offset);
  const uint16_t encryption = ReadBE16(data, format_offset + 4);
  const uint16_t compression = ReadBE16(data, format_offset + 6);
  if (encryption != 0) {
    // Only reached once the runtime, which holds the keys, has refused it.
    return rex::Err<XexImage>(rex::ErrorCategory::Format,
                              "The runtime could not load this encrypted XEX");
  }

  const uint8_t* payload = data.data() + header_size;
  const size_t payload_size = data.size() - header_size;
  if (compression == 0) {  // none
    std::memcpy(image.bytes.data(), payload, std::min<size_t>(payload_size, image_size));
  } else if (compression == 1) {  // basic: runs of data, each followed by zeroes
    size_t source = 0;
    size_t dest = 0;
    for (size_t record = format_offset + 8; record + 8 <= format_offset + format_size;
         record += 8) {
      const uint32_t data_size = ReadBE32(data, record);
      const uint32_t zero_size = ReadBE32(data, record + 4);
      if (source + data_size > payload_size || dest + data_size + zero_size > image_size) {
        return rex::Err<XexImage>(rex::ErrorCategory::Format, "The XEX image is truncated");
      }
      std::memcpy(image.bytes.data() + dest, payload + source, data_size);
      source += data_size;
      dest += data_size + zero_size;
    }
  } else if (compression == 2) {  // normal: hashed blocks of LZX chunks
    const uint32_t window_size = ReadBE32(data, format_offset + 8);
    uint32_t block_size = ReadBE32(data, format_offset + 12);
    std::vector<uint8_t> compressed;
    size_t block = 0;
    while (block_size) {
      if (block + block_size > payload_size || block_size < 24) {
        return rex::Err<XexImage>(rex::ErrorCategory::Format, "The XEX image is truncated");
      }
      const uint8_t* p = payload + block;
      // Each block starts with the size and hash of the block after it.
      const uint32_t next_size =
          (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3];
      size_t chunk = block + 24;
      const size_t block_end = block + block_size;
      while (chunk + 2 <= block_end) {
        const size_t length = (size_t(payload[chunk]) << 8) | payload[chunk + 1];
        chunk += 2;
        if (!length || chunk + length > block_end) {
          break;
        }
        compressed.insert(compressed.end(), payload + chunk, payload + chunk + length);
        chunk += length;
      }
      block = block_end;
      block_size = next_size;
    }
    if (lzx_decompress(compressed.data(), compressed.size(), image.bytes.data(), image_size,
                       window_size, nullptr, 0) != 0) {
      return rex::Err<XexImage>(rex::ErrorCategory::Format, "The XEX image did not decompress");
    }
  } else {
    return rex::Err<XexImage>(rex::ErrorCategory::Format,
                              fmt::format("Unknown XEX compression {}", compression));
  }

  const uint32_t resource_size = ReadBE32(data, resource_offset);
  for (size_t entry = resource_offset + 4; entry + 16 <= size_t(resource_offset) + resource_size;
       entry += 16) {
    char name[8];
    std::memcpy(name, data.data() + entry, 8);
    const uint32_t address = ReadBE32(data, entry + 8);
    const uint32_t size = ReadBE32(data, entry + 12);
    Resource resource{SafeName(name), nullptr, size};
    if (address >= image.base && size_t(address - image.base) + size <= image.bytes.size()) {
      resource.data = image.bytes.data() + (address - image.base);
    }
    image.resources.push_back(std::move(resource));
  }
  return image;
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

  std::vector<Resource> resources;
  XexImage direct;
  const std::string vfs_path = "game:\\" + xex_path.filename().string();
  status = runtime->LoadXexImage(vfs_path);
  auto module = status == X_STATUS_SUCCESS ? runtime->kernel_state()->GetExecutableModule()
                                           : nullptr;
  if (module) {
    rex::xex2_opt_resource_info* header = nullptr;
    if (module->GetOptHeader(rex::XEX_HEADER_RESOURCE_INFO,
                             reinterpret_cast<void**>(&header)) != X_STATUS_SUCCESS ||
        !header) {
      return rex::Err(rex::ErrorCategory::NotFound, "The XEX carries no resources");
    }
    const uint32_t count = (header->size - 4) / uint32_t(sizeof(rex::xex2_resource));
    for (uint32_t i = 0; i < count; ++i) {
      const auto& resource = header->resources[i];
      resources.push_back({SafeName(resource.name),
                           runtime->memory()->TranslateVirtual(resource.address),
                           uint32_t(resource.size)});
    }
  } else {
    REXLOG_INFO("The runtime would not load {} as a module; reading its image directly",
                xex_path.filename().string());
    auto image = ReadImageDirect(xex_path);
    if (!image) {
      return rex::Err(image.error().category, fmt::format("Failed to read {}: {}",
                                                          xex_path.string(),
                                                          image.error().message));
    }
    direct = std::move(*image);
    resources = direct.resources;
  }

  const uint32_t count = uint32_t(resources.size());
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

  for (const Resource& resource : resources) {
    if (!resource.data || resource.size == 0) {
      REXLOG_WARN("  {} is empty or outside the image", resource.name);
      continue;
    }
    REXLOG_INFO("  {:<10} {:>10} bytes  {}", resource.name, resource.size,
                DescribeBlob(resource.data, resource.size));
    if (!extracting) {
      continue;
    }
    const fs::path target = output / resource.name;
    std::ofstream file(target, std::ios::binary);
    if (!file || !file.write(reinterpret_cast<const char*>(resource.data),
                             std::streamsize(resource.size))) {
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
