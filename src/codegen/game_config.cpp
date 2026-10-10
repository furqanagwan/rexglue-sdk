/**
 * @file        codegen/game_config.cpp
 * @brief       PC MicrosoftGame.config generation for recompiled titles (RG-GDK-022)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/codegen/game_config.h>

#include <array>
#include <cctype>
#include <regex>
#include <string_view>

#include <fmt/format.h>

namespace rex::codegen {

namespace {

constexpr std::array<GameConfigImage, 5> kImages = {{
    {"StoreLogo", "StoreLogo.png", 100, 100},
    {"Square150x150Logo", "Square150x150Logo.png", 150, 150},
    {"Square44x44Logo", "Square44x44Logo.png", 44, 44},
    {"Square480x480Logo", "Square480x480Logo.png", 480, 480},
    {"SplashScreenImage", "SplashScreen.png", 1920, 1080},
}};

Result<void> Invalid(std::string_view field, std::string_view value, std::string_view rule) {
  return Err<void>(ErrorCategory::Validation,
                   fmt::format("{} \"{}\" is invalid: {}", field, value, rule));
}

bool Matches(const std::string& value, const char* pattern) {
  return std::regex_match(value, std::regex(pattern));
}

bool HasControlCharacter(std::string_view value) {
  for (unsigned char c : value) {
    if (c < 0x20 || c == 0x7F) {
      return true;
    }
  }
  return false;
}

bool Trimmed(std::string_view value) {
  return !value.empty() && !std::isspace(static_cast<unsigned char>(value.front())) &&
         !std::isspace(static_cast<unsigned char>(value.back()));
}

bool IsVersionQuad(const std::string& value) {
  static const char* kPart = "(0|[1-9][0-9]{0,4})";
  if (!Matches(value, fmt::format("{0}\\.{0}\\.{0}\\.{0}", kPart).c_str())) {
    return false;
  }
  size_t start = 0;
  while (start <= value.size()) {
    size_t end = value.find('.', start);
    if (end == std::string::npos) {
      end = value.size();
    }
    if (std::stoul(value.substr(start, end - start)) > 65535) {
      return false;
    }
    start = end + 1;
  }
  return true;
}

bool IsRelativeExecutable(std::string_view path) {
  if (path.size() < 5 || HasControlCharacter(path) ||
      path.find_first_of("<>\":%|?*") != std::string_view::npos) {
    return false;
  }
  std::string lower(path.substr(path.size() - 4));
  for (char& c : lower) {
    c = char(std::tolower(static_cast<unsigned char>(c)));
  }
  if (lower != ".exe") {
    return false;
  }
  size_t start = 0;
  while (start <= path.size()) {
    size_t end = path.find_first_of("\\/", start);
    if (end == std::string_view::npos) {
      end = path.size();
    }
    const auto part = path.substr(start, end - start);
    if (part.empty() || part.front() == '.' || part.back() == '.') {
      return false;
    }
    start = end + 1;
  }
  return true;
}

Result<void> CheckDisplayName(std::string_view field, const std::string& value) {
  if (!Trimmed(value) || value.size() > 256 || HasControlCharacter(value)) {
    return Invalid(field, value,
                   "1-256 characters, no control characters or surrounding whitespace");
  }
  return Ok();
}

std::string EscapeXml(std::string_view value) {
  std::string out;
  out.reserve(value.size());
  for (char c : value) {
    switch (c) {
      case '&':
        out += "&amp;";
        break;
      case '<':
        out += "&lt;";
        break;
      case '>':
        out += "&gt;";
        break;
      case '"':
        out += "&quot;";
        break;
      case '\'':
        out += "&apos;";
        break;
      default:
        out += c;
    }
  }
  return out;
}

uint32_t Crc32(const uint8_t* data, size_t size, uint32_t crc = 0) {
  crc = ~crc;
  for (size_t i = 0; i < size; ++i) {
    crc ^= data[i];
    for (int bit = 0; bit < 8; ++bit) {
      crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
    }
  }
  return ~crc;
}

void PutBe32(std::vector<uint8_t>& out, uint32_t value) {
  out.push_back(uint8_t(value >> 24));
  out.push_back(uint8_t(value >> 16));
  out.push_back(uint8_t(value >> 8));
  out.push_back(uint8_t(value));
}

void PutChunk(std::vector<uint8_t>& out, const char type[4], const std::vector<uint8_t>& data) {
  PutBe32(out, uint32_t(data.size()));
  const size_t type_at = out.size();
  out.insert(out.end(), type, type + 4);
  out.insert(out.end(), data.begin(), data.end());
  PutBe32(out, Crc32(out.data() + type_at, 4 + data.size()));
}

class RunLengthDeflater {
 public:
  std::vector<uint8_t> Compress(const std::vector<uint8_t>& data) {
    PutBits(1, 1);
    PutBits(1, 2);
    size_t i = 0;
    while (i < data.size()) {
      size_t run = 0;
      if (i > 0) {
        while (run < 258 && i + run < data.size() && data[i + run] == data[i - 1]) {
          ++run;
        }
      }
      if (run >= 3) {
        PutLength(uint32_t(run));
        PutBits(0, 5);
        i += run;
      } else {
        PutSymbol(data[i++]);
      }
    }
    PutSymbol(256);
    if (bit_count_) {
      out_.push_back(uint8_t(bits_));
    }
    return std::move(out_);
  }

 private:
  void PutBits(uint32_t value, int count) {
    bits_ |= value << bit_count_;
    bit_count_ += count;
    while (bit_count_ >= 8) {
      out_.push_back(uint8_t(bits_));
      bits_ >>= 8;
      bit_count_ -= 8;
    }
  }

  void PutCode(uint32_t code, int length) {
    uint32_t reversed = 0;
    for (int b = 0; b < length; ++b) {
      reversed |= ((code >> b) & 1) << (length - 1 - b);
    }
    PutBits(reversed, length);
  }

  void PutSymbol(uint32_t symbol) {
    if (symbol < 144) {
      PutCode(0x30 + symbol, 8);
    } else if (symbol < 256) {
      PutCode(0x190 + symbol - 144, 9);
    } else if (symbol < 280) {
      PutCode(symbol - 256, 7);
    } else {
      PutCode(0xC0 + symbol - 280, 8);
    }
  }

  void PutLength(uint32_t length) {
    static constexpr uint16_t kBase[29] = {3,  4,  5,  6,   7,   8,   9,   10,  11, 13,
                                           15, 17, 19, 23,  27,  31,  35,  43,  51, 59,
                                           67, 83, 99, 115, 131, 163, 195, 227, 258};
    static constexpr uint8_t kExtra[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2,
                                           2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
    int code = 28;
    while (kBase[code] > length || (code == 28 && length != 258)) {
      --code;
    }
    PutSymbol(257 + code);
    PutBits(length - kBase[code], kExtra[code]);
  }

  std::vector<uint8_t> out_;
  uint32_t bits_ = 0;
  int bit_count_ = 0;
};

uint32_t Adler32(const std::vector<uint8_t>& data) {
  uint32_t a = 1, b = 0;
  for (uint8_t byte : data) {
    a = (a + byte) % 65521;
    b = (b + a) % 65521;
  }
  return (b << 16) | a;
}

}

std::span<const GameConfigImage> GameConfigImages() {
  return kImages;
}

Result<void> ValidateGameConfigIdentity(const GameConfigIdentity& id) {
  if (!Matches(id.name, "[-.A-Za-z0-9]{3,50}")) {
    return Invalid("Identity name", id.name, "3-50 characters from A-Z a-z 0-9 . -");
  }

  if (id.publisher.size() > 8192 ||
      !Matches(id.publisher,
               "(CN|L|O|OU|E|C|S|STREET|T|G|I|SN|DC|SERIALNUMBER)=([^,+=\"<>#;]+|\"[^\"]*\")"
               "(, (CN|L|O|OU|E|C|S|STREET|T|G|I|SN|DC|SERIALNUMBER)=([^,+=\"<>#;]+|\"[^\"]*\"))"
               "*")) {
    return Invalid("Publisher", id.publisher,
                   "an X.500 name such as CN=Example or CN=Example, O=Studio");
  }
  if (!IsVersionQuad(id.version)) {
    return Invalid("Version", id.version, "four numbers 0-65535, e.g. 1.0.0.0");
  }
  if (auto r = CheckDisplayName("Display name", id.display_name); !r) {
    return r;
  }
  if (auto r = CheckDisplayName("Publisher display name", id.publisher_display_name); !r) {
    return r;
  }
  if (!id.description.empty() && (!Trimmed(id.description) || id.description.size() > 2048 ||
                                  HasControlCharacter(id.description))) {
    return Invalid("Description", id.description,
                   "up to 2048 characters, no control characters or surrounding whitespace");
  }
  if (!Matches(id.background_color, "#[0-9a-fA-F]{6}")) {
    return Invalid("Background color", id.background_color, "#RRGGBB");
  }
  if (!IsRelativeExecutable(id.executable)) {
    return Invalid("Executable", id.executable, "a relative path to the title's .exe");
  }
  if (id.title_id.has_value() != id.msa_app_id.has_value()) {
    return Err<void>(ErrorCategory::Validation,
                     "Title ID and MSA app ID come from Partner Center together: give both or "
                     "neither");
  }
  if (id.title_id) {
    if (!Matches(*id.title_id, "[0-9a-fA-F]{8}") || *id.title_id == "00000000") {
      return Invalid("Title ID", *id.title_id, "8 hex digits from Partner Center, not all zero");
    }
    if (!Trimmed(*id.msa_app_id) || HasControlCharacter(*id.msa_app_id) ||
        id.msa_app_id->find_first_not_of('0') == std::string::npos) {
      return Invalid("MSA app ID", *id.msa_app_id, "the MSA app ID from Partner Center");
    }
  }
  if (id.store_id && !Matches(*id.store_id, "[0-9bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ]{12}")) {
    return Invalid("Store ID", *id.store_id, "the 12-character Store ID from Partner Center");
  }
  return Ok();
}

Result<std::string> RenderGameConfig(const GameConfigIdentity& id) {
  if (auto valid = ValidateGameConfigIdentity(id); !valid) {
    return Err<std::string>(valid.error());
  }
  std::string xml;
  xml += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
  xml += "<!-- Generated by rexglue init gameconfig. IDs appear only when supplied. -->\n";
  xml += "<Game configVersion=\"1\">\n";
  xml += fmt::format("  <Identity Name=\"{}\" Publisher=\"{}\" Version=\"{}\"/>\n",
                     EscapeXml(id.name), EscapeXml(id.publisher), id.version);
  if (id.store_id) {
    xml += fmt::format("  <StoreId>{}</StoreId>\n", *id.store_id);
  }
  if (id.title_id) {
    xml += fmt::format("  <MSAAppId>{}</MSAAppId>\n", EscapeXml(*id.msa_app_id));
    xml += fmt::format("  <TitleId>{}</TitleId>\n", *id.title_id);
  }
  xml += "  <ExecutableList>\n";
  xml += fmt::format(
      "    <Executable Name=\"{}\" TargetDeviceFamily=\"PC\" Architecture=\"x64\" "
      "Id=\"Game\"/>\n",
      EscapeXml(id.executable));
  xml += "  </ExecutableList>\n";
  xml += "  <ShellVisuals";
  xml += fmt::format("\n    DefaultDisplayName=\"{}\"", EscapeXml(id.display_name));
  xml += fmt::format("\n    PublisherDisplayName=\"{}\"", EscapeXml(id.publisher_display_name));
  if (!id.description.empty()) {
    xml += fmt::format("\n    Description=\"{}\"", EscapeXml(id.description));
  }
  xml += fmt::format("\n    BackgroundColor=\"{}\"", id.background_color);
  xml += "\n    ForegroundText=\"light\"";
  for (const auto& image : kImages) {
    xml += fmt::format("\n    {}=\"{}\"", image.attribute, image.file_name);
  }
  xml += "/>\n";

  xml += "  <DesktopRegistration>\n";
  xml += "    <DependencyList>\n";
  xml += "      <KnownDependency Name=\"VC14\"/>\n";
  xml += "    </DependencyList>\n";
  xml += "  </DesktopRegistration>\n";
  xml += "</Game>\n";
  return xml;
}

std::vector<uint8_t> SolidColorPng(uint32_t width, uint32_t height, uint32_t rgb) {
  std::vector<uint8_t> png = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};

  std::vector<uint8_t> header;
  PutBe32(header, width);
  PutBe32(header, height);

  header.insert(header.end(), {8, 6, 0, 0, 0});
  PutChunk(png, "IHDR", header);

  const size_t row_bytes = 1 + size_t(width) * 4;
  std::vector<uint8_t> raw(row_bytes * height, 0);
  for (size_t row = 0; row < height; ++row) {
    uint8_t* line = raw.data() + row * row_bytes;
    line[0] = 1;
    line[1] = uint8_t(rgb >> 16);
    line[2] = uint8_t(rgb >> 8);
    line[3] = uint8_t(rgb);
    line[4] = 0xFF;
  }
  std::vector<uint8_t> zlib = {0x78, 0x01};
  const auto deflated = RunLengthDeflater().Compress(raw);
  zlib.insert(zlib.end(), deflated.begin(), deflated.end());
  PutBe32(zlib, Adler32(raw));
  PutChunk(png, "IDAT", zlib);
  PutChunk(png, "IEND", {});
  return png;
}

}
