/**
 * @file        rexglue/commands/library_art_command.cpp
 * @brief       rexglue library-art: a title's Xbox PC library tiles (RG-GDK-068)
 *
 * Makes the GDK ShellVisuals images (Square480x480Logo, Square150x150Logo,
 * StoreLogo, Square44x44Logo and SplashScreen), and LibraryTile (1080 x 1080)
 * for a game added to the Xbox app by hand, in the style the Xbox PC app
 * shows Xbox 360 backward-compatible games in: the game's box art beside a
 * white strip with the green swooshes, the XBOX 360 wordmark and the orb. The
 * box art and splash come from the 360 marketplace (download.xbox.com) or
 * the builder's own files; the wordmark and orb from the builder's console
 * system update, as for the guide. Nothing of it ships with the SDK. The
 * window and EXE icon are separate (RG-GDK-060) and are not touched.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "library_art_command.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <rex/logging.h>
#include <rex/ui/xui/runtime.h>
#include <rex/ui/xui/system_update.h>

#include "http_client.h"
#include "library_art.h"

namespace rexglue::cli {

using rex::Err;
using rex::ErrorCategory;
using rex::Result;

namespace {

// The 360 marketplace's box art carries the console's banner (the orb,
// XBOX 360 and LIVE) across its top 13%.
constexpr double kMarketplaceBanner = 0.13;

struct LibraryArtArgs {
  std::string title_id;
  std::string cover;
  std::string background;
  std::vector<std::string> system_update;
  std::string output;
};

std::optional<std::vector<uint8_t>> ReadFile(const std::filesystem::path& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return std::nullopt;
  }
  return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
}

Result<void> WritePng(const Image& image, const std::filesystem::path& path) {
  std::string error;
  const auto png = EncodePng(image, &error);
  if (!png) {
    return Err<void>(ErrorCategory::IO, fmt::format("{}: {}", path.string(), error));
  }
  std::ofstream file(path, std::ios::binary | std::ios::trunc);
  file.write(reinterpret_cast<const char*>(png->data()), std::streamsize(png->size()));
  if (!file) {
    return Err<void>(ErrorCategory::IO, fmt::format("could not write {}", path.string()));
  }
  return rex::Ok();
}

// The title's image from the 360 marketplace: boxartlg.jpg (219 x 300) or
// background.jpg (1280 x 720).
std::optional<Image> Marketplace(const std::string& title_id, std::string_view file,
                                 std::string* error) {
  std::string id = title_id;
  std::transform(id.begin(), id.end(), id.begin(),
                 [](unsigned char c) { return char(std::tolower(c)); });
  const std::string url = fmt::format(
      "http://download.xbox.com/content/images/66acd000-77fe-1000-9115-d802{}/1033/{}", id, file);
  auto bytes = HttpGet(url, error);
  return bytes ? DecodeImage(*bytes, error) : std::nullopt;
}

std::optional<Image> Local(const std::string& path, std::string* error) {
  auto bytes = ReadFile(path);
  if (!bytes) {
    *error = fmt::format("{}: cannot be read", path);
    return std::nullopt;
  }
  auto image = DecodeImage(*bytes, error);
  if (!image) {
    *error = fmt::format("{}: {}", path, *error);
  }
  return image;
}

Result<void> WriteLibraryArt(const LibraryArtArgs& args) {
  std::string title = args.title_id;
  if (title.starts_with("0x") || title.starts_with("0X")) {
    title = title.substr(2);
  }
  if (!title.empty() && (title.size() != 8 || !std::all_of(title.begin(), title.end(), [](char c) {
                           return std::isxdigit(static_cast<unsigned char>(c));
                         }))) {
    return Err<void>(ErrorCategory::Config,
                     fmt::format("{}: a title ID is eight hex digits", args.title_id));
  }
  if (title.empty() && args.cover.empty()) {
    return Err<void>(ErrorCategory::Config, "give the title ID or --cover");
  }
  std::string error;
  // The box art: the builder's own (no banner), or the marketplace's.
  std::optional<Image> cover;
  double crop_top = 0.0;
  if (!args.cover.empty()) {
    cover = Local(args.cover, &error);
  } else {
    cover = Marketplace(title, "boxartlg.jpg", &error);
    crop_top = kMarketplaceBanner;
  }
  if (!cover) {
    return Err<void>(ErrorCategory::IO, fmt::format("box art: {}", error));
  }

  // The orb and wordmark from the console's own splash_360.png.
  std::optional<StripArt> strip;
  if (!args.system_update.empty()) {
    using rex::ui::xui::SystemUpdate;
    const std::vector<std::filesystem::path> sources(args.system_update.begin(),
                                                     args.system_update.end());
    auto modules = SystemUpdate::ReadModules(sources, &error);
    std::unique_ptr<SystemUpdate> update;
    if (modules && (update = SystemUpdate::FromModules(*modules, &error))) {
      const auto splash = DecodeImage(
          rex::ui::xui::ResolveFile(*update, "sharedres://splash_360.png", "xam/xam"), &error);
      if (splash) {
        strip = StripArtFromSplash(*splash, &error);
      }
    }
    if (!strip) {
      REXLOG_WARN("Library art: no XBOX 360 wordmark or orb ({}); the strip has the swooshes only",
                  error);
    }
  } else {
    REXLOG_WARN("Library art: no --system-update; the strip has the swooshes only");
  }

  const std::filesystem::path out(args.output);
  std::error_code ec;
  std::filesystem::create_directories(out, ec);
  const Image master = ComposeTile(*cover, crop_top, strip ? &*strip : nullptr, 1080);
  struct Tile {
    const char* name;
    int size;
  };
  // The four ShellVisuals sizes, and the full tile for the Xbox app's own
  // artwork choice on a game added by hand.
  for (const Tile& tile : {Tile{"LibraryTile.png", 1080}, Tile{"Square480x480Logo.png", 480},
                           Tile{"Square150x150Logo.png", 150}, Tile{"StoreLogo.png", 100},
                           Tile{"Square44x44Logo.png", 44}}) {
    if (auto written = WritePng(Resize(master, tile.size, tile.size), out / tile.name); !written) {
      return written;
    }
  }

  // The splash: the title's key art, as the BC packages show.
  std::optional<Image> background;
  if (!args.background.empty()) {
    background = Local(args.background, &error);
  } else if (!title.empty()) {
    background = Marketplace(title, "background.jpg", &error);
  }
  if (background) {
    if (auto written = WritePng(Cover(*background, 1920, 1080), out / "SplashScreen.png");
        !written) {
      return written;
    }
  } else {
    REXLOG_WARN("Library art: no splash ({}); SplashScreen.png is left as it is", error);
  }
  REXLOG_INFO("Library art: tiles{} -> {}", background ? " and splash" : "", out.string());
  return rex::Ok();
}

}  // namespace

void RegisterLibraryArt(CLI::App& parent, const CliContext& ctx, DeferredAction& pending) {
  (void)ctx;
  auto args = std::make_shared<LibraryArtArgs>();
  auto* sub = parent.add_subcommand(
      "library-art",
      "Make a title's Xbox PC library tiles in the Xbox 360 backward-compatibility style");
  sub->add_option("title_id", args->title_id,
                  "Title ID, eight hex digits: box art and splash from the 360 marketplace");
  sub->add_option("--cover", args->cover, "Box art to use instead, without the console banner")
      ->type_name("PATH");
  sub->add_option("--background", args->background, "Key art for the splash instead")
      ->type_name("PATH");
  sub->add_option("--system-update", args->system_update,
                  "$SystemUpdate folder, its package or a BC Flash folder, for the XBOX 360 "
                  "wordmark and orb (as for guide-bundle)")
      ->type_name("PATH");
  sub->add_option("-o,--output", args->output, "Folder for the PNGs (a title's gdk folder)")
      ->required()
      ->type_name("PATH");
  sub->callback([args, &pending]() {
    pending = [args]() -> Result<void> { return WriteLibraryArt(*args); };
  });
}

}  // namespace rexglue::cli
