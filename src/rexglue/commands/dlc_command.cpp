/**
 * @file        rexglue/commands/dlc_command.cpp
 * @brief       rexglue dlc-catalog and dlc-find: a title's add-ons from the 360 marketplace
 *              catalogue (RG-GDK-050)
 *
 * The Xbox 360 marketplace catalogue (catalog.xboxlive.com, the service the
 * console's marketplace queried) still answers FindGames. Add-ons are media
 * type 18, each naming its game's media ID (66ACD000-77FE-1000-9115-D802 and
 * the title ID). It has no filter by game, so dlc-find pages through every
 * add-on once and prints the [[dlc]] entries for a title's config;
 * dlc-catalog then fetches only those IDs, at build time, with their art.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "dlc_command.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <future>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <rex/logging.h>
#include <rex/string/utf8.h>
#include <rex/ui/guide/dlc_catalog.h>

#include "http_client.h"

// clang-format off
#include <windows.h>
// clang-format on

namespace rexglue::cli {

using rex::Err;
using rex::ErrorCategory;
using rex::Result;
using rex::ui::guide::DlcCatalogEntry;

namespace {

constexpr std::string_view kCatalog = "http://catalog.xboxlive.com/Catalog/Catalog.asmx/Query";
constexpr int kAddOnMediaType = 18;
constexpr int kPageSize = 300;
constexpr int kMaxPages = 1000;

constexpr std::string_view kBannerImage = "27";
constexpr std::string_view kTileImage = "23";

std::string QueryUrl(std::string_view locale, int page, int page_size,
                     const std::vector<std::string>& ids) {
  std::string url = fmt::format(
      "{}?methodName=FindGames&Names=Locale&Values={}&Names=LegalLocale&Values={}"
      "&Names=Store&Values=1&Names=PageSize&Values={}&Names=PageNum&Values={}"
      "&Names=DetailView&Values=5&Names=OfferFilterLevel&Values=1&Names=UserTypes&Values=2"
      "&Names=MediaTypes&Values={}",
      kCatalog, locale, locale, page_size, page, kAddOnMediaType);
  for (const std::string& id : ids) {
    url += fmt::format("&Names=MediaIds&Values={}", id);
  }
  return url;
}

std::string DefaultLocale() {
  wchar_t name[LOCALE_NAME_MAX_LENGTH] = {};
  if (!GetUserDefaultLocaleName(name, LOCALE_NAME_MAX_LENGTH)) {
    return "en-US";
  }
  std::string out;
  for (const wchar_t* c = name; *c; ++c) {
    out += char(*c);
  }
  return out;
}

std::string DecodeEntities(std::string_view text) {
  std::string out;
  for (size_t i = 0; i < text.size(); ++i) {
    if (text[i] != '&') {
      out += text[i];
      continue;
    }
    const size_t end = text.find(';', i);
    if (end == std::string_view::npos) {
      out += text[i];
      continue;
    }
    const std::string_view name = text.substr(i + 1, end - i - 1);
    if (name == "amp") {
      out += '&';
    } else if (name == "lt") {
      out += '<';
    } else if (name == "gt") {
      out += '>';
    } else if (name == "quot") {
      out += '"';
    } else if (name == "apos") {
      out += '\'';
    } else if (name.starts_with('#')) {
      const bool hex = name.size() > 1 && (name[1] == 'x' || name[1] == 'X');
      const uint32_t code = uint32_t(
          std::strtoul(std::string(name.substr(hex ? 2 : 1)).c_str(), nullptr, hex ? 16 : 10));
      if (code < 0x80) {
        out += char(code);
      } else if (code < 0x800) {
        out += char(0xC0 | (code >> 6));
        out += char(0x80 | (code & 0x3F));
      } else if (code < 0x10000) {
        out += char(0xE0 | (code >> 12));
        out += char(0x80 | ((code >> 6) & 0x3F));
        out += char(0x80 | (code & 0x3F));
      } else {
        out += char(0xF0 | (code >> 18));
        out += char(0x80 | ((code >> 12) & 0x3F));
        out += char(0x80 | ((code >> 6) & 0x3F));
        out += char(0x80 | (code & 0x3F));
      }
    } else {
      out += text.substr(i, end - i + 1);
    }
    i = end;
  }
  return out;
}

std::string Tag(std::string_view xml, std::string_view tag) {
  const std::string open = fmt::format("<{}>", tag);
  const std::string close = fmt::format("</{}>", tag);
  const size_t start = xml.find(open);
  if (start == std::string_view::npos) {
    return {};
  }
  const size_t end = xml.find(close, start);
  if (end == std::string_view::npos) {
    return {};
  }
  std::string text = DecodeEntities(xml.substr(start + open.size(), end - start - open.size()));

  const auto space = [](unsigned char c) { return std::isspace(c) != 0; };
  while (!text.empty() && space(text.back())) {
    text.pop_back();
  }
  const auto first = std::find_if_not(text.begin(), text.end(), space);
  return std::string(first, text.end());
}

std::vector<std::string_view> Entries(std::string_view feed) {
  std::vector<std::string_view> out;
  for (size_t at = 0;;) {
    const size_t start = feed.find("<entry ", at);
    if (start == std::string_view::npos) {
      break;
    }
    const size_t end = feed.find("</entry>", start);
    if (end == std::string_view::npos) {
      break;
    }
    out.push_back(feed.substr(start, end - start));
    at = end;
  }
  return out;
}

std::string Upper(std::string text) {
  std::transform(text.begin(), text.end(), text.begin(),
                 [](unsigned char c) { return char(std::toupper(c)); });
  return text;
}

std::string MediaId(std::string_view entry) {
  std::string id = Tag(entry, "id");
  if (id.starts_with("urn:uuid:")) {
    id = id.substr(9);
  }
  return Upper(std::move(id));
}

std::string ImageUrl(std::string_view entry, std::string_view relationship) {
  for (size_t at = 0;;) {
    const size_t start = entry.find("<live:image>", at);
    if (start == std::string_view::npos) {
      return {};
    }
    const size_t end = entry.find("</live:image>", start);
    const std::string_view image = entry.substr(start, end - start);
    if (Tag(image, "live:relationshipType") == relationship) {
      return Tag(image, "live:fileUrl");
    }
    at = end;
  }
}

std::optional<std::string> Fetch(const std::string& url, std::string* error) {
  auto body = HttpGet(url, error, 60000);
  if (!body) {
    return std::nullopt;
  }
  std::string text(body->begin(), body->end());
  if (text.find("<Exception>") != std::string::npos) {
    if (error) {
      *error =
          fmt::format("{}: the catalogue refused the query ({})", url, Tag(text, "HResultName"));
    }
    return std::nullopt;
  }
  return text;
}

struct CatalogArgs {
  std::vector<std::string> ids;
  std::string locale;
  std::string output;
};

Result<void> WriteCatalog(const CatalogArgs& args) {
  const std::string locale = args.locale.empty() ? DefaultLocale() : args.locale;
  std::vector<DlcCatalogEntry> entries;
  for (const std::string& id : args.ids) {
    DlcCatalogEntry entry;
    entry.id = Upper(id);
    entries.push_back(std::move(entry));
  }
  std::string error;

  std::optional<std::string> feed;
  if (!entries.empty()) {
    feed = Fetch(QueryUrl(locale, 1, int(args.ids.size()), args.ids), &error);
  }
  if (!feed && !entries.empty()) {
    REXLOG_WARN("DLC catalogue: {}; building it with IDs only", error);
  }
  size_t found = 0;
  for (std::string_view xml : feed ? Entries(*feed) : std::vector<std::string_view>{}) {
    const std::string id = MediaId(xml);
    auto it = std::find_if(entries.begin(), entries.end(),
                           [&](const DlcCatalogEntry& e) { return e.id == id; });
    if (it == entries.end()) {
      continue;
    }
    ++found;
    it->title = Tag(xml, "live:fullTitle");
    if (it->title.empty()) {
      it->title = Tag(xml, "title");
    }
    it->description = Tag(xml, "live:description");
    if (it->description.empty()) {
      it->description = Tag(xml, "live:reducedDescription");
    }
    it->publisher = Tag(xml, "live:publisher");
    it->developer = Tag(xml, "live:developer");
    it->release_date = Tag(xml, "live:releaseDate").substr(0, 10);
    auto image = [&](std::string_view relationship) {
      const std::string url = ImageUrl(xml, relationship);
      std::string image_error;
      auto bytes = url.empty() ? std::nullopt : HttpGet(url, &image_error);
      if (!url.empty() && !bytes) {
        REXLOG_WARN("DLC catalogue: {}", image_error);
      }
      return bytes.value_or(std::vector<uint8_t>{});
    };
    it->banner = image(kBannerImage);
    it->tile = image(kTileImage);
  }
  if (feed && found < entries.size()) {
    for (const DlcCatalogEntry& e : entries) {
      if (e.title.empty()) {
        REXLOG_WARN("DLC catalogue: {} is not in the {} catalogue", e.id, locale);
      }
    }
  }

  const auto bytes = rex::ui::guide::WriteDlcCatalog(entries);
  const std::filesystem::path out(args.output);
  std::error_code ec;
  if (out.has_parent_path()) {
    std::filesystem::create_directories(out.parent_path(), ec);
  }
  const std::filesystem::path temp = out.string() + ".tmp";
  {
    std::ofstream file(temp, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(bytes.data()), std::streamsize(bytes.size()));
    if (!file) {
      return Err<void>(ErrorCategory::IO, fmt::format("could not write {}", temp.string()));
    }
  }
  std::filesystem::rename(temp, out, ec);
  if (ec) {
    return Err<void>(ErrorCategory::IO,
                     fmt::format("could not write {}: {}", out.string(), ec.message()));
  }
  REXLOG_INFO("DLC catalogue: {} of {} add-ons from the {} catalogue, {} KiB -> {}", found,
              entries.size(), locale, bytes.size() / 1024, out.string());
  return rex::Ok();
}

struct FindArgs {
  std::string title_id;
  std::string locale;
};

Result<void> FindDlc(const FindArgs& args) {
  const std::string locale = args.locale.empty() ? DefaultLocale() : args.locale;
  std::string title = Upper(args.title_id);
  if (title.starts_with("0X")) {
    title = title.substr(2);
  }
  if (title.size() != 8 || !std::all_of(title.begin(), title.end(), [](char c) {
        return std::isxdigit(static_cast<unsigned char>(c));
      })) {
    return Err<void>(ErrorCategory::Config,
                     fmt::format("{}: a title ID is eight hex digits", args.title_id));
  }
  const std::string game = "66ACD000-77FE-1000-9115-D802" + title;
  std::string error;
  auto first = Fetch(QueryUrl(locale, 1, kPageSize, {}), &error);
  if (!first) {
    return Err<void>(ErrorCategory::IO, error);
  }
  const int total = std::atoi(Tag(*first, "live:totalItems").c_str());
  const int pages = std::min(kMaxPages, (total + kPageSize - 1) / kPageSize);
  REXLOG_INFO("DLC find: {} add-ons in the {} catalogue, {} pages", total, locale, pages);

  struct Hit {
    std::string id, name;
  };
  auto scan = [&](const std::string& feed) {
    std::vector<Hit> hits;
    for (std::string_view xml : Entries(feed)) {
      std::string parent = Upper(Tag(xml, "live:gameTitleMediaId"));
      if (parent.starts_with("URN:UUID:")) {
        parent = parent.substr(9);
      }
      if (parent == game) {
        hits.push_back({MediaId(xml), Tag(xml, "title")});
      }
    }
    return hits;
  };
  std::vector<Hit> hits = scan(*first);

  for (int page = 2; page <= pages; page += 6) {
    std::vector<std::future<std::optional<std::string>>> batch;
    for (int p = page; p < page + 6 && p <= pages; ++p) {
      batch.push_back(std::async(std::launch::async, [&locale, p] {
        std::string page_error;
        auto feed = Fetch(QueryUrl(locale, p, kPageSize, {}), &page_error);
        if (!feed) {
          REXLOG_WARN("DLC find: page {}: {}", p, page_error);
        }
        return feed;
      }));
    }
    for (auto& f : batch) {
      if (auto feed = f.get()) {
        auto more = scan(*feed);
        hits.insert(hits.end(), more.begin(), more.end());
      }
    }
  }
  if (hits.empty()) {
    fmt::print("# No add-ons for title {} in the {} catalogue.\n", title, locale);
    return rex::Ok();
  }
  fmt::print("# Add-ons for title {} in the {} catalogue: paste into the title's config.\n", title,
             locale);
  for (const Hit& hit : hits) {
    fmt::print("\n[[dlc]]\nid = \"{}\"  # {}\n", hit.id, hit.name);
  }
  return rex::Ok();
}

}

void RegisterDlcCommands(CLI::App& parent, const CliContext& ctx, DeferredAction& pending) {
  (void)ctx;
  auto catalog = std::make_shared<CatalogArgs>();
  auto* sub = parent.add_subcommand(
      "dlc-catalog", "Fetch a title's add-ons from the 360 marketplace catalogue for embedding");
  sub->add_option("--ids", catalog->ids, "Marketplace media IDs of the add-ons ([[dlc]] id)")
      ->delimiter(',');
  sub->add_option("--locale", catalog->locale,
                  "Catalogue language and market, such as en-GB (default: this PC's)");
  sub->add_option("-o,--output", catalog->output, "Catalogue file to write")
      ->required()
      ->type_name("PATH");
  sub->callback([catalog, &pending]() {
    pending = [catalog]() -> Result<void> { return WriteCatalog(*catalog); };
  });

  auto find = std::make_shared<FindArgs>();
  auto* find_sub = parent.add_subcommand(
      "dlc-find", "List a title's add-ons in the 360 marketplace catalogue as [[dlc]] entries");
  find_sub->add_option("title_id", find->title_id, "Title ID, eight hex digits")->required();
  find_sub->add_option("--locale", find->locale,
                       "Catalogue language and market, such as en-GB (default: this PC's)");
  find_sub->callback(
      [find, &pending]() { pending = [find]() -> Result<void> { return FindDlc(*find); }; });
}

}
